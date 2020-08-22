#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>
#include <fstream>
#include <strstream>
#include <algorithm>


using namespace std;

struct vec3d
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 1.0f; // Need a 4th term to perform sensible matrix vector multiplication
};

struct triangle
{
    vec3d p[3];
    sf::Color triangleColor;
};

struct mesh
{
    vector<triangle> tris;

    bool LoadFromObjectFile(std::string sFileName)
    {
        std::ifstream fileStream(sFileName);
        if (!fileStream.is_open())
        {
            return false;
        }
        //Local cache of vertexes
        vector<vec3d> vertexes;

        while (!fileStream.eof())
        {
            int buffSize = 128;
            char line[buffSize];
            fileStream.getline(line, buffSize);

            strstream stringStream;
            stringStream << line;

            char junk;

            if (line[0] == 'v')
            {
                vec3d v;
                stringStream >> junk >> v.x >> v.y >> v.z;
                vertexes.push_back(v);
            }
            if (line[0] == 'f')
            {
                int triangleStr[3];
                stringStream >> junk >> triangleStr[0] >> triangleStr[1] >> triangleStr[2];

                tris.push_back({vertexes[triangleStr[0] - 1],
                                vertexes[triangleStr[1] - 1],
                                vertexes[triangleStr[2] - 1]});
            }
        }
        return true;
    }
};

struct mat4x4
{
    float m[4][4] = {0};
};

class olcEngine3D
{
public:
    olcEngine3D(int width, int height)
    {
        this->height = height;
        this->width = width;
    }

    vec3d vCamera;
    float fYaw;

    int width, height;

    float fTheta = 0.0f;    // Spins World transform

    mesh textureMesh;
    mat4x4 matProj;    // Matrix that converts from view space to screen space
    vec3d vLookDir;




    vec3d MatrixMultiplyVector(mat4x4 &matrix, vec3d &vec3D) noexcept
    {
        vec3d v;
        v.x = vec3D.x * matrix.m[0][0] + vec3D.y * matrix.m[1][0] + vec3D.z * matrix.m[2][0] + vec3D.w * matrix.m[3][0];
        v.y = vec3D.x * matrix.m[0][1] + vec3D.y * matrix.m[1][1] + vec3D.z * matrix.m[2][1] + vec3D.w * matrix.m[3][1];
        v.z = vec3D.x * matrix.m[0][2] + vec3D.y * matrix.m[1][2] + vec3D.z * matrix.m[2][2] + vec3D.w * matrix.m[3][2];
        v.w = vec3D.x * matrix.m[0][3] + vec3D.y * matrix.m[1][3] + vec3D.z * matrix.m[2][3] + vec3D.w * matrix.m[3][3];
        return v;
    }

    mat4x4 MatrixMakeIdentity() noexcept
    {
        mat4x4 matrix;
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 MatrixMakeRotationX(float fAngleRad) noexcept
    {
        mat4x4 matrix;
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = cosf(fAngleRad);
        matrix.m[1][2] = sinf(fAngleRad);
        matrix.m[2][1] = -sinf(fAngleRad);
        matrix.m[2][2] = cosf(fAngleRad);
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 MatrixMakeRotationY(float fAngleRad) noexcept
    {
        mat4x4 matrix;
        matrix.m[0][0] = cosf(fAngleRad);
        matrix.m[0][2] = sinf(fAngleRad);
        matrix.m[2][0] = -sinf(fAngleRad);
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = cosf(fAngleRad);
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 MatrixMakeRotationZ(float fAngleRad) noexcept
    {
        mat4x4 matrix;
        matrix.m[0][0] = cosf(fAngleRad);
        matrix.m[0][1] = sinf(fAngleRad);
        matrix.m[1][0] = -sinf(fAngleRad);
        matrix.m[1][1] = cosf(fAngleRad);
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 MatrixMakeTranslation(float x, float y, float z) noexcept
    {
        mat4x4 matrix;
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        matrix.m[3][0] = x;
        matrix.m[3][1] = y;
        matrix.m[3][2] = z;
        return matrix;
    }

    mat4x4 MatrixMakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar) noexcept
    {
        float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
        mat4x4 matrix;
        matrix.m[0][0] = fAspectRatio * fFovRad;
        matrix.m[1][1] = fFovRad;
        matrix.m[2][2] = fFar / (fFar - fNear);
        matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matrix.m[2][3] = 1.0f;
        matrix.m[3][3] = 0.0f;
        return matrix;
    }

    mat4x4 MatrixMultiplyMatrix(mat4x4 &firstMat, mat4x4 &secondMat) noexcept
    {
        mat4x4 matrix;
        for (int c = 0; c < 4; c++)
        {
            for (int r = 0; r < 4; r++)
            {
                matrix.m[r][c] = firstMat.m[r][0] * secondMat.m[0][c] +
                                 firstMat.m[r][1] * secondMat.m[1][c] +
                                 firstMat.m[r][2] * secondMat.m[2][c] +
                                 firstMat.m[r][3] * secondMat.m[3][c];
            }
        }
        return matrix;
    }

    mat4x4 MatrixPointAt(vec3d &pos, vec3d &target, vec3d &up)
    {
        // Calculate new forward direction
        vec3d newForward = VectorSub(target, pos);
        newForward = VectorNormalise(newForward);

        // Calculate new Up direction
        float dotUpAndForward = VectorDotProduct(up, newForward);
        vec3d multiplyNew = VectorMul(newForward, dotUpAndForward);
        vec3d newUp = VectorSub(up, multiplyNew);
        newUp = VectorNormalise(newUp);

        // New Right direction (cross product)
        vec3d newRight = VectorCrossProduct(newUp, newForward);

        // Construct Dimensioning and Translation Matrix
        mat4x4 mat;
        mat.m[0][0] = newRight.x;    mat.m[0][1] = newRight.y;    mat.m[0][2] = newRight.z;    mat.m[0][3] = 0.0f;
        mat.m[1][0] = newUp.x;       mat.m[1][1] = newUp.y;       mat.m[1][2] = newUp.z;       mat.m[1][3] = 0.0f;
        mat.m[2][0] = newForward.x;  mat.m[2][1] = newForward.y;  mat.m[2][2] = newForward.z;  mat.m[2][3] = 0.0f;
        mat.m[3][0] = pos.x;         mat.m[3][1] = pos.y;         mat.m[3][2] = pos.z;         mat.m[3][3] = 1.0f;

        return mat;
    }

    mat4x4 MatrixQuickInverse(mat4x4 &m) // Only for Rotation/Translation Matrices
    {
        mat4x4 matrix;

        matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
        matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
        matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
        matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
        matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
        matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
        matrix.m[3][3] = 1.0f;

        return matrix;
    }

    vec3d VectorAdd(vec3d &firstVect, vec3d &secondVect)
    {
        return {firstVect.x + secondVect.x, firstVect.y + secondVect.y, firstVect.z + secondVect.z };
    }

    vec3d VectorSub(vec3d &firstVect, vec3d &secondVect)
    {
        return {firstVect.x - secondVect.x, firstVect.y - secondVect.y, firstVect.z - secondVect.z };
    }

    vec3d VectorMul(vec3d &vect3D, float k)
    {
        return {vect3D.x * k, vect3D.y * k, vect3D.z * k };
    }

    vec3d VectorDiv(vec3d &vect3D, float k)
    {
        return {vect3D.x / k, vect3D.y / k, vect3D.z / k };
    }

    float VectorDotProduct(vec3d &firstVect, vec3d &secondVect)
    {
        return firstVect.x * secondVect.x + firstVect.y * secondVect.y + firstVect.z * secondVect.z;
    }

    float VectorLength(vec3d &vector3D)
    {
        return sqrtf(VectorDotProduct(vector3D, vector3D));
    }

    vec3d VectorNormalise(vec3d &vector3D)
    {
        float l = VectorLength(vector3D);
        return {vector3D.x / l, vector3D.y / l, vector3D.z / l };
    }

    vec3d VectorCrossProduct(vec3d &firstVect, vec3d &secondVect)
    {
        vec3d v;
        v.x = firstVect.y * secondVect.z - firstVect.z * secondVect.y;
        v.y = firstVect.z * secondVect.x - firstVect.x * secondVect.z;
        v.z = firstVect.x * secondVect.y - firstVect.y * secondVect.x;
        return v;
    }

public:
    bool OnUserCreate()
    {
        string textureLocation = "/home/dmitry/Documents/GitHub/cpptasks/GraphicsEngine/textureMesh.obj";
        string teapot = "/home/dmitry/Desktop/teapot.obj";
        string axis = "/home/dmitry/Desktop/axis.obj";
        textureMesh.LoadFromObjectFile(axis);

        matProj = MatrixMakeProjection(90.0f, (float)height/ width, 0.1f, 1000.0f);

        return true;
    }

    void DrawTriangle(sf::RenderWindow &window, float x, float y, float x1, float y1, float x2, float y2)
    {
        sf::VertexArray lines(sf::LinesStrip, 2);
        lines[0].position = sf::Vector2f(x, y);
        lines[1].position = sf::Vector2f(x1, y1);
        window.draw(lines);

        lines[0].position = sf::Vector2f(x1, y1);
        lines[1].position = sf::Vector2f(x2, y2);
        window.draw(lines);

        lines[0].position = sf::Vector2f(x2, y2);
        lines[1].position = sf::Vector2f(x, y);
        window.draw(lines);
    }

    void FillTriangle(sf::RenderWindow &window, float x, float y, float x1, float y1, float x2, float y2, sf::Color c)
    {
        sf::VertexArray triangle(sf::Triangles, 3);

        // define the position of the triangle's points
        triangle[0].position = sf::Vector2f(x, y);
        triangle[1].position = sf::Vector2f(x1, y1);
        triangle[2].position = sf::Vector2f(x2, y2);

        // define the color of the triangle's points

        triangle[0].color = c;
        triangle[1].color = c;
        triangle[2].color = c;

        window.draw(triangle);
    }

    sf::Color ColorFromFloat(float zeroOneInterval)
    {
        return sf::Color(255, 255, 255, 255 * zeroOneInterval);
    }


    bool OnUserUpdate(float fElapsedTime, sf::RenderWindow &window)
    {
        //fTheta += fElapsedTime * 3.1415f;

        mat4x4 matRotZ, matRotX;
        matRotZ = MatrixMakeRotationZ(fTheta * 0.5);
        matRotX = MatrixMakeRotationX(fTheta);

        mat4x4 matTrans;
        matTrans = MatrixMakeTranslation(0.0f, 0.0f, 5.0f);

        mat4x4 matWorld;
        matWorld = MatrixMakeIdentity();	// Form World Matrix
        matWorld = MatrixMultiplyMatrix(matRotX, matRotZ); // Transform by rotation
        matWorld = MatrixMultiplyMatrix(matWorld, matTrans); // Transform by translation

        vec3d vUp = {0, 1, 0};
        vec3d vTarget = {0, 0, 1};
        mat4x4 matCameraRot = MatrixMakeRotationY(fYaw);
        vLookDir = MatrixMultiplyVector(matCameraRot, vTarget);
        vTarget = VectorAdd(vCamera, vLookDir);


        mat4x4 matCamera = MatrixPointAt(vCamera, vTarget, vUp);

        // Make view matrix from camera
        mat4x4 matView = MatrixQuickInverse(matCamera);

        vector<triangle> vectorTriangleToRaster;

        // Draw Triangles
        for (auto tri : textureMesh.tris)
        {
            triangle triProjected, triTransformed, triViewed;

            // World Matrix Transform
            triTransformed.p[0] = MatrixMultiplyVector(matWorld, tri.p[0]);
            triTransformed.p[1] = MatrixMultiplyVector(matWorld, tri.p[1]);
            triTransformed.p[2] = MatrixMultiplyVector(matWorld, tri.p[2]);

            // Calculate triangle Normal
            vec3d normal, line1, line2;

            // Get lines either side of triangle
            line1 = VectorSub(triTransformed.p[1], triTransformed.p[0]);
            line2 = VectorSub(triTransformed.p[2], triTransformed.p[0]);

            // Take cross product of lines to get normal to triangle surface
            normal = VectorCrossProduct(line1, line2);

            // You normally need to normalise a normal!
            normal = VectorNormalise(normal);

            // Get Ray from triangle to camera
            vec3d vCameraRay = VectorSub(triTransformed.p[0], vCamera);

            // If ray is aligned with normal, then triangle is visible
            if (VectorDotProduct(normal, vCameraRay) < 0.0f)
            {
                // Illumination
                vec3d light_direction = { 0.0f, 1.0f, -1.0f };
                light_direction = VectorNormalise(light_direction);

                // How "aligned" are light direction and triangle surface normal?
                float depth = max(0.1f, VectorDotProduct(light_direction, normal));


                triProjected.triangleColor = ColorFromFloat(depth);

                // Convert World Space --> View Space
                triViewed.p[0] = MatrixMultiplyVector(matView, triTransformed.p[0]);
                triViewed.p[1] = MatrixMultiplyVector(matView, triTransformed.p[1]);
                triViewed.p[2] = MatrixMultiplyVector(matView, triTransformed.p[2]);

                // Project triangles from 3D --> 2D
                triProjected.p[0] = MatrixMultiplyVector(matProj, triViewed.p[0]);
                triProjected.p[1] = MatrixMultiplyVector(matProj, triViewed.p[1]);
                triProjected.p[2] = MatrixMultiplyVector(matProj, triViewed.p[2]);

                triProjected.p[0] = VectorDiv(triProjected.p[0], triProjected.p[0].w);
                triProjected.p[1] = VectorDiv(triProjected.p[1], triProjected.p[1].w);
                triProjected.p[2] = VectorDiv(triProjected.p[2], triProjected.p[2].w);

                // Scale into view
                vec3d vOffsetView = {1, 1, 0};
                triProjected.p[0] = VectorAdd(triProjected.p[0], vOffsetView);
                triProjected.p[1] = VectorAdd(triProjected.p[1], vOffsetView);
                triProjected.p[2] = VectorAdd(triProjected.p[2], vOffsetView);

                triProjected.p[0].x *= 0.5f * (float) width;
                triProjected.p[0].y *= 0.5f * (float) height;
                triProjected.p[1].x *= 0.5f * (float) width;
                triProjected.p[1].y *= 0.5f * (float) height;
                triProjected.p[2].x *= 0.5f * (float) width;
                triProjected.p[2].y *= 0.5f * (float) height;

                vectorTriangleToRaster.push_back(triProjected);
            }
            // Store triangles for sorting
        }
        sort(vectorTriangleToRaster.begin(), vectorTriangleToRaster.end(),
             [](triangle &t1, triangle &t2)
             {
                 float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                 float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
                 return z1 > z2;
             });

        for (auto &triProjected : vectorTriangleToRaster)
        {
            // Rasterize triangle
            FillTriangle(window, triProjected.p[0].x, triProjected.p[0].y,
                         triProjected.p[1].x, triProjected.p[1].y,
                         triProjected.p[2].x, triProjected.p[2].y, triProjected.triangleColor);
        }


        return true;
    }

};

int main()
{
    const float fElapsedTime = 0.1f;

    olcEngine3D engine3D(640, 480);
    engine3D.OnUserCreate();

    sf::RenderWindow window(sf::VideoMode(640, 480), "Vertex Graphing");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                engine3D.vCamera.y -= 8.0f * fElapsedTime;	// Travel Y Upwards
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                engine3D.vCamera.y += 8.0f * fElapsedTime;	// Travel Y Downwards
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                engine3D.vCamera.x -= 8.0f * fElapsedTime;	// Travel X Lefter
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                engine3D.vCamera.x += 8.0f * fElapsedTime;	// Travel X Righter
            }

            vec3d vForward = engine3D.VectorMul(engine3D.vLookDir, 8.0f * fElapsedTime);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                engine3D.fYaw -= 1.0f * fElapsedTime;	// Change yaw (left)
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                engine3D.fYaw += 1.0f * fElapsedTime;	// Change yaw (right)
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                engine3D.vCamera = engine3D.VectorAdd(engine3D.vCamera, vForward);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                engine3D.vCamera = engine3D.VectorSub(engine3D.vCamera, vForward);
            }
        }
        engine3D.OnUserUpdate(fElapsedTime, window);
        window.display();
        window.clear();
    }
    return 0;
}

