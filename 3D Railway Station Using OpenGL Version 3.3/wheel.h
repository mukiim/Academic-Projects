
#ifndef wheel_h
#define wheel_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

# define PI 3.1416

using namespace std;

//const int MIN_SECTOR_COUNT1 = 3;
//const int MIN_STACK_COUNT1 = 2;

class Wheel
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    // ctor/dtor
    Wheel(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, glm::vec3 amb = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 diff = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f), float shiny = 32.0f) : verticesStride(24)
    {
        set(radius, sectorCount, stackCount, amb, diff, spec, shiny);
        buildCoordinatesAndIndices();
        buildVertices();

        glGenVertexArrays(1, &sphereVAO);
        glBindVertexArray(sphereVAO);

        // create VBO to copy vertex data to VBO
        unsigned int sphereVBO;
        glGenBuffers(1, &sphereVBO);
        glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);           // for vertex data
        glBufferData(GL_ARRAY_BUFFER,                   // target
            this->getVertexSize(), // data size, # of bytes
            this->getVertices(),   // ptr to vertex data
            GL_STATIC_DRAW);                   // usage

        // create EBO to copy index data
        unsigned int sphereEBO;
        glGenBuffers(1, &sphereEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);   // for index data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
            this->getIndexSize(),             // data size, # of bytes
            this->getIndices(),               // ptr to index data
            GL_STATIC_DRAW);                   // usage

        // activate attrib arrays
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // set attrib arrays with stride and offset
        int stride = this->getVerticesStride();     // should be 24 bytes
        glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

        // unbind VAO and VBOs
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




        glGenVertexArrays(1, &sphereVAO2);
        glBindVertexArray(sphereVAO2);

        // create VBO to copy vertex data to VBO
        unsigned int sphereVBO2;
        glGenBuffers(1, &sphereVBO2);
        glBindBuffer(GL_ARRAY_BUFFER, sphereVBO2);           // for vertex data
        glBufferData(GL_ARRAY_BUFFER,                   // target
            vertices2.size() * sizeof(float), // data size, # of bytes
            vertices2.data(),   // ptr to vertex data
            GL_STATIC_DRAW);                   // usage

        // create EBO to copy index data
        unsigned int sphereEBO2;
        glGenBuffers(1, &sphereEBO2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO2);   // for index data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
            indices2.size() * sizeof(unsigned int),             // data size, # of bytes
            indices2.data() ,               // ptr to index data
            GL_STATIC_DRAW);                   // usage

        // activate attrib arrays
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // set attrib arrays with stride and offset
        //stride = this->getVerticesStride();     // should be 24 bytes
        glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

        // unbind VAO and VBOs
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    ~Wheel() {}

    // getters/setters

    void set(float radius, int sectors, int stacks, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        if (radius > 0)
            this->radius = radius;
        this->sectorCount = sectors;
        if (sectors < MIN_SECTOR_COUNT1)
            this->sectorCount = MIN_SECTOR_COUNT1;
        this->stackCount = stacks;
        if (stacks < MIN_STACK_COUNT1)
            this->stackCount = MIN_STACK_COUNT1;
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;
    }

    void setRadius(float radius)
    {
        if (radius != this->radius)
            set(radius, sectorCount, stackCount, ambient, diffuse, specular, shininess);
    }

    void setSectorCount(int sectors)
    {
        if (sectors != this->sectorCount)
            set(radius, sectors, stackCount, ambient, diffuse, specular, shininess);
    }

    void setStackCount(int stacks)
    {
        if (stacks != this->stackCount)
            set(radius, sectorCount, stacks, ambient, diffuse, specular, shininess);
    }

    // for interleaved vertices
    unsigned int getVertexCount() const
    {
        return (unsigned int)coordinates.size() / 3;     // # of vertices
    }

    unsigned int getVertexSize() const
    {
        return (unsigned int)vertices.size() * sizeof(float);  // # of bytes
    }

    int getVerticesStride() const
    {
        return verticesStride;   // should be 24 bytes
    }
    const float* getVertices() const
    {
        return vertices.data();
    }

    unsigned int getIndexSize() const
    {
        return (unsigned int)indices.size() * sizeof(unsigned int);
    }

    const unsigned int* getIndices() const
    {
        return indices.data();
    }

    unsigned int getIndexCount() const
    {
        return (unsigned int)indices.size();
    }

    // draw in VertexArray mode
    void drawSphere(Shader& lightingShader, glm::mat4 model) const      // draw surface
    {
        lightingShader.use();

        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model);

        // draw a sphere with VAO
        glBindVertexArray(sphereVAO);
        glDrawElements(GL_TRIANGLES,                    // primitive type
            this->getIndexCount(),          // # of indices
            GL_UNSIGNED_INT,                 // data type
            (void*)0);                       // offset to indices

        // unbind VAO
        glBindVertexArray(0);
    }
    void drawWheel(Shader& lightingShader, glm::mat4 model) const      // draw surface
    {
        drawSphere(lightingShader, model);
        glm::mat4 scale = glm::mat4(1.0f);

        scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0, 1.0, 2.0));
        drawSphere(lightingShader, model*scale);

        lightingShader.use();

        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model* glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 18.0, 0.0)));

        // draw a sphere with VAO
        glBindVertexArray(sphereVAO2);
        glDrawElements(GL_TRIANGLES,                    // primitive type
            indices2.size(),          // # of indices
            GL_UNSIGNED_INT,                 // data type
            (void*)0);                       // offset to indices

        // unbind VAO
        glBindVertexArray(0);

        lightingShader.use();

        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model);

        // draw a sphere with VAO
        glBindVertexArray(sphereVAO2);
        glDrawElements(GL_TRIANGLES,                    // primitive type
            indices2.size(),          // # of indices
            GL_UNSIGNED_INT,                 // data type
            (void*)0);                       // offset to indices

        // unbind VAO
        glBindVertexArray(0);

    }

private:
    // member functions
    //void buildCoordinatesAndIndices()
    //{
    //    float x, y, z, xz;                              // vertex position
    //    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal

    //    float sectorStep = 2 * PI / sectorCount;
    //    float stackStep = PI / stackCount;
    //    float sectorAngle = -sectorStep;
    //    float stackAngle = PI / 2 + stackStep;


    void buildCoordinatesAndIndices()
    {
        float x, y = 0, z, xz;                              // vertex position
        float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
        float sectorStep = 2 * PI / sectorCount;
        float sectorAngle = -sectorStep;
        

        float stackStep = 18 / stackCount;             //18 is the length of axis so (18/18 =1)
        //float stackAngle = PI / 2 + stackStep;


        for (int i = 0; i <= stackCount; ++i)
        {
                        
            y = y + stackStep;
            // add (sectorCount+1) vertices per stack
            // first and last vertices have same position and normal, but different tex coords
            for (int j = 0; j <= sectorCount; ++j)
            {
                
                sectorAngle += sectorStep;           // starting from 0 to 2pi

                // vertex position (x, y, z)
                z = radius * cosf(sectorAngle);
                x = radius * sinf(sectorAngle);
                coordinates.push_back(x);
                coordinates.push_back(y);
                coordinates.push_back(z);

                // normalized vertex normal (nx, ny, nz)
                nx = (x) / sqrt(pow(x, 2)+ pow(z, 2));
                ny = 0.0;
                nz = (z) / sqrt(pow(x, 2)+ pow(z, 2));

                normals.push_back(nx);
                normals.push_back(ny);
                normals.push_back(nz);
                if (i == 0)
                {
                    coordinates2.push_back(x);
                    coordinates2.push_back(y);
                    coordinates2.push_back(z);

                    normals2.push_back(nx);
                    normals2.push_back(ny);
                    normals2.push_back(nz);

                }
            }
            if (i == 0)
            {
                sectorAngle = -sectorStep;
                
                for (int k = 0; k <= sectorCount; k++)
                {
                    sectorAngle += sectorStep;
                    z = (radius+1) * cosf(sectorAngle);
                    x = (radius + 1) * sinf(sectorAngle);
                    coordinates2.push_back(x);
                    coordinates2.push_back(y);
                    coordinates2.push_back(z);

                    normals2.push_back(nx);
                    normals2.push_back(ny);
                    normals2.push_back(nz);
                }
            }

        }

        // generate index list of sphere triangles
        // k1--k1+1
        // |  / |
        // | /  |
        // k2--k2+1

        int k1, k2;
        for (int i = 0; i < stackCount; ++i)
        {
            k1 = i * (sectorCount + 1);     // beginning of current stack
            k2 = k1 + sectorCount + 1;      // beginning of next stack

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                // 2 triangles per sector excluding first and last stacks
                
                    // k1 => k2 => k1+1
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);

                    // k1+1 => k2 => k2+1
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1); 
            }
        }
       
         k1 =0;     // beginning of current stack
         k2 = k1 + sectorCount + 1;      // beginning of next stack

         for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                // 2 triangles per sector excluding first and last stacks

                    // k1 => k2 => k1+1
                indices2.push_back(k1 + 1);
                indices2.push_back(k2);                
                indices2.push_back(k1);

                // k1+1 => k2 => k2+1
                indices2.push_back(k1 + 1);
                indices2.push_back(k2 + 1);
                indices2.push_back(k2);
                
            }
        
        
    }

    void buildVertices()
    {
        size_t i, j;
        size_t count = coordinates.size();
        for (i = 0, j = 0; i < count; i += 3, j += 2)
        {
            vertices.push_back(coordinates[i]);
            vertices.push_back(coordinates[i + 1]);
            vertices.push_back(coordinates[i + 2]);

            vertices.push_back(normals[i]);
            vertices.push_back(normals[i + 1]);
            vertices.push_back(normals[i + 2]);
        }
        count = coordinates2.size();
        for (i = 0, j = 0; i < count; i += 3, j += 2)
        {
            vertices2.push_back(coordinates2[i]);
            vertices2.push_back(coordinates2[i + 1]);
            vertices2.push_back(coordinates2[i + 2]);

            vertices2.push_back(normals2[i]);
            vertices2.push_back(normals2[i + 1]);
            vertices2.push_back(normals2[i + 2]);
        }
    }

    //    for (int i = 0; i <= stackCount; ++i)
    //    {
    //        stackAngle -= stackStep;        // starting from pi/2 to -pi/2
    //        xz = radius * cosf(stackAngle);
    //        y = radius * sinf(stackAngle);
    //        // add (sectorCount+1) vertices per stack
    //        // first and last vertices have same position and normal, but different tex coords
    //        for (int j = 0; j <= sectorCount; ++j)
    //        {
    //            sectorAngle += sectorStep;           // starting from 0 to 2pi

    //            // vertex position (x, y, z)
    //            z = xz * cosf(sectorAngle);
    //            x = xz * sinf(sectorAngle);
    //            coordinates.push_back(x);
    //            coordinates.push_back(y);
    //            coordinates.push_back(z);

    //            // normalized vertex normal (nx, ny, nz)
    //            nx = x * lengthInv;
    //            ny = y * lengthInv;
    //            nz = z * lengthInv;
    //            normals.push_back(nx);
    //            normals.push_back(ny);
    //            normals.push_back(nz);
    //        }
    //    }

    //    // generate index list of sphere triangles
    //    // k1--k1+1
    //    // |  / |
    //    // | /  |
    //    // k2--k2+1

    //    int k1, k2;
    //    for (int i = 0; i < stackCount; ++i)
    //    {
    //        k1 = i * (sectorCount + 1);     // beginning of current stack
    //        k2 = k1 + sectorCount + 1;      // beginning of next stack

    //        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
    //        {
    //            // 2 triangles per sector excluding first and last stacks
    //            if (i != 0 && i != (stackCount - 1))
    //            {
    //                // k1 => k2 => k1+1
    //                indices.push_back(k1);
    //                indices.push_back(k2);
    //                indices.push_back(k1 + 1);

    //                // k1+1 => k2 => k2+1
    //                indices.push_back(k1 + 1);
    //                indices.push_back(k2);
    //                indices.push_back(k2 + 1);
    //            }
    //            // 2 triangles per sector excluding first and last stacks
    //            else if (i == 0)
    //            {
    //                indices.push_back(k1 + 1);
    //                indices.push_back(k2);
    //                indices.push_back(k2 + 1);

    //            }

    //            else if (i == (stackCount - 1))
    //            {
    //                indices.push_back(k1);
    //                indices.push_back(k2);
    //                indices.push_back(k1 + 1);
    //            }
    //        }
    //    }
    //}

    //void buildVertices()
    //{
    //    size_t i, j;
    //    size_t count = coordinates.size();
    //    for (i = 0, j = 0; i < count; i += 3, j += 2)
    //    {
    //        vertices.push_back(coordinates[i]);
    //        vertices.push_back(coordinates[i + 1]);
    //        vertices.push_back(coordinates[i + 2]);

    //        vertices.push_back(normals[i]);
    //        vertices.push_back(normals[i + 1]);
    //        vertices.push_back(normals[i + 2]);
    //    }
    //}




    vector<float> computeFaceNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
    {
        const float EPSILON = 0.000001f;

        vector<float> normal(3, 0.0f);     // default return value (0,0,0)
        float nx, ny, nz;

        // find 2 edge vectors: v1-v2, v1-v3
        float ex1 = x2 - x1;
        float ey1 = y2 - y1;
        float ez1 = z2 - z1;
        float ex2 = x3 - x1;
        float ey2 = y3 - y1;
        float ez2 = z3 - z1;

        // cross product: e1 x e2
        nx = ey1 * ez2 - ez1 * ey2;
        ny = ez1 * ex2 - ex1 * ez2;
        nz = ex1 * ey2 - ey1 * ex2;

        // normalize only if the length is > 0
        float length = sqrtf(nx * nx + ny * ny + nz * nz);
        if (length > EPSILON)
        {
            // normalize
            float lengthInv = 1.0f / length;
            normal[0] = nx * lengthInv;
            normal[1] = ny * lengthInv;
            normal[2] = nz * lengthInv;
        }

        return normal;
    }

    // memeber vars
    unsigned int sphereVAO, sphereVAO2;
    float radius;
    int sectorCount;                        // longitude, # of slices
    int stackCount;                         // latitude, # of stacks
    vector<float> vertices,vertices2;
    vector<float> normals, normals2;
    vector<unsigned int> indices, indices2;
    vector<float> coordinates, coordinates2;
    int verticesStride;                 // # of bytes to hop to the next vertex (should be 24 bytes)

};


#endif /* sphere_h */


