#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>
#include <fstream>
#include <strstream>

using namespace std;

struct vec3d
{
    float x, y, z;
};

struct triangle
{
    vec3d p[3];
};

struct mesh
{
    vector<triangle> tris;

    bool LoadFromObjectFile(std::string sFileName)
    {
        std::ifstream fileStream(sFileName);
        if(!fileStream.is_open())
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
        const wchar_t m_sAppName[8] = L"3D Demo";
    }


private:
    int width, height;

    mesh meshCube;
    mat4x4 matProj;

    vec3d vCamera;

    float fTheta;

    void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
    {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

        if (w != 0.0f)
        {
            o.x /= w;
            o.y /= w;
            o.z /= w;
        }
    }

public:
    bool OnUserCreate()
    {

        string textureLocation = "/home/dmitry/Documents/GitHub/cpptasks/GraphicsEngine/textureMesh.obj";
        bool isRead = meshCube.LoadFromObjectFile(textureLocation);
        printf("Read: %i\n", isRead);

        // Projection Matrix
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRatio = (float) height / (float) width;
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;

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
        return sf::Color(255, 255, 255, 255*zeroOneInterval);
    }


    bool OnUserUpdate(float fElapsedTime, sf::RenderWindow &window)
    {

        // Set up rotation matrices
        mat4x4 matRotZ, matRotX;
        fTheta += 1.0f * fElapsedTime;

        // Rotation Z
        matRotZ.m[0][0] = cosf(fTheta);
        matRotZ.m[0][1] = sinf(fTheta);
        matRotZ.m[1][0] = -sinf(fTheta);
        matRotZ.m[1][1] = cosf(fTheta);
        matRotZ.m[2][2] = 1;
        matRotZ.m[3][3] = 1;

        // Rotation X
        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(fTheta * 0.5f);
        matRotX.m[1][2] = sinf(fTheta * 0.5f);
        matRotX.m[2][1] = -sinf(fTheta * 0.5f);
        matRotX.m[2][2] = cosf(fTheta * 0.5f);
        matRotX.m[3][3] = 1;

        

        // Draw Triangles
        for (auto tri : meshCube.tris)
        {
            triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

            // Rotate in Z-Axis
            MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
            MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
            MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

            // Rotate in X-Axis
            MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
            MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
            MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

            // Offset into the screen
            triTranslated = triRotatedZX;
            triTranslated.p[0].z = triRotatedZX.p[0].z + 8.0f;
            triTranslated.p[1].z = triRotatedZX.p[1].z + 8.0f;
            triTranslated.p[2].z = triRotatedZX.p[2].z + 8.0f;

            // Computing the normal
            vec3d line1, line2, normal;
            line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
            line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
            line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

            line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
            line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
            line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

            normal.x = line1.y * line2.z - line1.z * line2.y;
            normal.y = line1.z * line2.x - line1.x * line2.z;
            normal.z = line1.x * line2.y - line1.y * line2.x;

            //Normalizing the normal

            float len = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
            normal.x /= len;
            normal.y /= len;
            normal.z /= len;

            float dotProductX = normal.x * (triTranslated.p[0].x - vCamera.x);
            float dotProductY =  normal.y * (triTranslated.p[0].y - vCamera.y);
            float dotProductZ = normal.z * (triTranslated.p[0].z - vCamera.z);
            float dotProd = dotProductX + dotProductY + dotProductZ;

            if (dotProd < 0.0f)
            {
                //Illumination
                vec3d lightDirection = {0.0f, 0.0f, -1.0f};

                float lightVecLength = sqrtf(lightDirection.x * lightDirection.x +
                                                lightDirection.y * lightDirection.y +
                                                lightDirection.z * lightDirection.z);
                lightDirection.x /= lightVecLength;
                lightDirection.y /= lightVecLength;
                lightDirection.z /= lightVecLength;

                float depth = lightDirection.x * normal.x +
                              lightDirection.y * normal.y +
                              lightDirection.z * normal.z;
                sf::Color color = ColorFromFloat(depth);


                // Project triangles from 3D --> 2D
                MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
                MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
                MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

                // Scale into view
                triProjected.p[0].x += 1.0f;
                triProjected.p[0].y += 1.0f;
                triProjected.p[1].x += 1.0f;
                triProjected.p[1].y += 1.0f;
                triProjected.p[2].x += 1.0f;
                triProjected.p[2].y += 1.0f;
                triProjected.p[0].x *= 0.5f * (float) width;
                triProjected.p[0].y *= 0.5f * (float) height;
                triProjected.p[1].x *= 0.5f * (float) width;
                triProjected.p[1].y *= 0.5f * (float) height;
                triProjected.p[2].x *= 0.5f * (float) width;
                triProjected.p[2].y *= 0.5f * (float) height;

                // Rasterize triangle
                FillTriangle(window, triProjected.p[0].x, triProjected.p[0].y,
                             triProjected.p[1].x, triProjected.p[1].y,
                             triProjected.p[2].x, triProjected.p[2].y, color);
            }
        }


        return true;
    }

};

int main()
{
    olcEngine3D engine3D(640, 480);
    engine3D.OnUserCreate();
    sf::RenderWindow window(sf::VideoMode(640, 480), "Graphing App");
    while (window.isOpen())
    {
        sf::Event event;
        engine3D.OnUserUpdate(0.0001, window);
        window.display();
        window.clear();
        window.clear();
    }
    return 0;
}

