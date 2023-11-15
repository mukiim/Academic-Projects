#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "cube.h"
#include "stb_image.h"
#include "semiCylinder.h"
#include "wheel.h"
#include "cylinder.h"
#include "sphere.h"
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void bogi(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix,unsigned int id);

void Table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void Chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void ultaChair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void SideWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void SideWall1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void FrontWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void FrontWall1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void joint(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void Roof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void Floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void BlackBoard(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void Window(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix,unsigned int x);
void Fan1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
void Fan2(Shader ourShader);
void Platform(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);

// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(-4.0f, 6.1f, 56.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

bool tr = true;
bool fn = true;

bool dl = true;
bool sl = true;

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(3.80f,  1.50f,  0.0f),
    glm::vec3(9.0f,  4.5f,  -11.0f),
    glm::vec3(3.80f,  1.50f,  -40.0f),
    glm::vec3(-19.0f,  4.5f,  -30+3.0f),
    glm::vec3(-19.0f,  4.5f,  3.0f),

    glm::vec3(-4.0f,  4.5f,  30 + 3.0f),
    glm::vec3(4.0f,  4.5f,  30 + 3.0f),
    glm::vec3(-12.0f,  4.5f,  30 + 3.0f),

    glm::vec3(-10+3.80f,  1.50f,  0.0f),
    glm::vec3(-10+3.80f,  1.50f,  -40.0f)
};


//glm::vec3(-0.5, 1, -0.5)


PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);
PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);
PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);
PointLight pointlight7(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);
PointLight pointlight8(

    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number
);

PointLight pointlight9(

    pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    9       // light number
);
PointLight pointlight10(

    pointLightPositions[9].x, pointLightPositions[9].y, pointLightPositions[9].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    10       // light number
);
// light settings
bool onOffToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


bool isRotate = false;
float fanSpeed = 3.7f;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");

    string diffuseMapPath = "platform.png";
    string specularMapPath = "platform.png";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "railpath.png";
    specularMapPath = "railpath.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube railpath = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "wood.png";
    specularMapPath = "wood.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wood = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "stone.png";
    specularMapPath = "stone.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube stone = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "entrance1.png";
    specularMapPath = "entrance1.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube entrance = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "maze.png";
    specularMapPath = "maze.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube maze = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "ticket.png";
    specularMapPath = "ticket.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube ticket = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "entry.png";
    specularMapPath = "entry.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube entry = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "platformtop.png";
    specularMapPath = "platformtop.png";


    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube platformtop = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    float move = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
       

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        // point light 5
        pointlight5.setUpPointLight(lightingShader);
        // point light 6
        pointlight6.setUpPointLight(lightingShader);
        // point light 7
        pointlight7.setUpPointLight(lightingShader);

        // point light 8
        pointlight8.setUpPointLight(lightingShader);
        // point light 9
        pointlight9.setUpPointLight(lightingShader);
        // point light 10
        pointlight10.setUpPointLight(lightingShader);

        lightingShader.setVec3("diectionalLight.directiaon", 1.0f, 5.0f, 10.0f);
        lightingShader.setVec3("diectionalLight.ambient", .2, .2, .2);
        lightingShader.setVec3("diectionalLight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("diectionalLight.specular", 1.0f, 1.0f, 1.0f);




        if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        {

            dl ^= 1;
            if (dl) {
                cout << "Direction Light On" << endl;
                lightingShader.setBool("dlighton", true);
            }

            else {
                cout << "Direction Light Off" << endl;
                lightingShader.setBool("dlighton", false);
            }
        }


        lightingShader.setVec3("spotlight.position", -0.5, 2, 32.5);
        lightingShader.setVec3("spotlight.direction", 0, -1, 0);
        lightingShader.setVec3("spotlight.ambient", .2, .2, .2);
        lightingShader.setVec3("spotlight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotlight.k_c", 1.0f);
        lightingShader.setFloat("spotlight.k_l", 0.09);
        lightingShader.setFloat("spotlight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(5.5f)));

        if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        {
            sl ^= 1;
            if (sl) {
                cout << "Spot Light On" << endl;
                lightingShader.setBool("spotlighton", true);
            }
                
            else {
                cout << "Spot Light Off" << endl;
                lightingShader.setBool("spotlighton", false);
            }
                

        }


        //pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
        //    1.0f, 1.0f, 1.0f,     // ambient
        //    1.0f, 1.0f, 1.0f,      // diffuse
        //    1.0f, 1.0f, 1.0f,        // specular
        //    1.0f,   //k_c
        //    0.09f,  //k_l
        //    0.032f, //k_q
        //    1,       // light number
        //    glm::cos(glm::radians(20.5f)),
        //    glm::cos(glm::radians(25.0f)),
        //    0, -1, 0
        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, translateMatrix2;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //bed(cubeVAO, lightingShader, model);

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.3f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        model = glm::mat4(1.0f);
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, move));
        for (unsigned int i = 0; i < 6; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, i*(-15.0f)));
            model = translateMatrix2 * translateMatrix;
            bogi(cubeVAO, lightingShader, model,0);
            if (i < 5) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, i * (-15.0f)));
                model = translateMatrix2 * translateMatrix;
                joint(cubeVAO, lightingShader, model);
            }

        }
        
        for (unsigned int i = 0; i < 6; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, i * (-15.0f)));
            model =  translateMatrix;
            bogi(cubeVAO, lightingShader, model,1);
            if (i < 5) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.0f, i * (-15.0f)));
                model = translateMatrix;
                joint(cubeVAO, lightingShader, model);
            }

        }
        

        for (unsigned int i = 0; i < 3; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.5f+i*3, 0.0f, 30.5f));
            Table(cubeVAO, lightingShader, translateMatrix);
        }

        for (unsigned int i = 0; i < 3; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.2f + i*3, 0.0f, 29.5f));
            ultaChair(cubeVAO, lightingShader, translateMatrix);
        }

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3-11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.902f, 0.549f, 0.075f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.902f, 0.549f, 0.075f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(3-11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.902f, 0.549f, 0.075f);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6 - 11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.902f, 0.549f, 0.075f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5 - 11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.137f, 0.941f, 0.043f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(9.0 - 11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.137f, 0.941f, 0.043f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(18.0 - 11.2f, 0.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.11f, 1.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.137f, 0.941f, 0.043f);
        /// ticket counter shesh


        translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, -1.0f, 2.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.32f, 0.5f));

        Wheel wheel = Wheel(1.0f, 36, 18, glm::vec3(0.776, 0.949, 0.757),
            glm::vec3(0.776, 0.949, 0.757),
            glm::vec3(0.776, 0.949, 0.757), 32.0f);
        Wheel wheel1 = Wheel(1.0f, 36, 18, glm::vec3(0.349, 0.91, 0.643),
            glm::vec3(0.349, 0.91, 0.643),
            glm::vec3(0.349, 0.91, 0.643), 32.0f);

        for (unsigned int i = 0; i < 6; i++) {
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.32f, 0.5f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, -1.0f, 2.5f - i*14));
            wheel.drawWheel(lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, -1.0f, 2.5f - i * 14));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.06f, 1.0f));
            wheel1.drawWheel(lightingShader, translateMatrix * scaleMatrix);
        }
        
        for (unsigned int i = 0; i < 6; i++) {
            /*translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.0f, -1.0f, 2.5f - i * 14));
            wheel.drawWheel(lightingShader, translateMatrix * scaleMatrix);*/

            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.32f, 0.5f));
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.0f, -1.0f, 2.5f - i * 14));
            wheel.drawWheel(lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.0f, -1.0f, 2.5f - i * 14));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.06f, 1.0f));
            wheel1.drawWheel(lightingShader, translateMatrix * scaleMatrix);
        }
        Wheel wheel2 = Wheel(1.0f, 36, 18, glm::vec3(0.024, 0.925, 0.961),
            glm::vec3(0.024, 0.925, 0.961),
            glm::vec3(0.024, 0.925, 0.961), 32.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0f, -1.0f, 30.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.25f, 0.5f));
        wheel2.drawWheel(lightingShader, translateMatrix * scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.0f, -1.0f, 30.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.25f, 0.5f));
        wheel2.drawWheel(lightingShader, translateMatrix * scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, -1.0f, 30.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.25f, 0.5f));
        wheel2.drawWheel(lightingShader, translateMatrix * scaleMatrix);
        /*semiCylinder s = semiCylinder(0.65f, 36, 18, glm::vec3((float)255 / 255, (float)89 / 255, (float)0.0 / 255),
            glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255),
            glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.32f, 0.5f));
        s.drawsemiCylinder(lightingShader, rotateZMatrix * translateMatrix * scaleMatrix);*/

        

        /// ekhan theke texture
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);



        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        // point light 5
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        // point light 6
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        // point light 7
        pointlight7.setUpPointLight(lightingShaderWithTexture);

        // point light 8
        pointlight8.setUpPointLight(lightingShaderWithTexture);
        // point light 9
        pointlight9.setUpPointLight(lightingShaderWithTexture);
        // point light 10
        pointlight10.setUpPointLight(lightingShaderWithTexture);
        //glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        //modelMatrixForContainer = glm::translate(model, glm::vec3(-0.45f, -0.4f, -2.8f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 moveMatrix;

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.25f + 0.45f, -6.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.0f, 0.55f, 160.0f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -3.0f, 5-144.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;

        
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-30.0f, 1.25f + 0.45f, -6.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.0f, 0.55f, 160.0f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -3.0f, 5-144.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;


        cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-30.0f, 7.25f + 0.45f, -6.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.0f, 0.55f, 160.0f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -3.0f, 5-144.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;


        platformtop.drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 7.25f + 0.45f, -6.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.0f, 0.55f, 160.0f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -3.0f, 5-144.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;


        platformtop.drawCubeWithTexture(lightingShaderWithTexture, model);

        float railTrackX = -0.5, railTrackY = -1.45, railTrackZ = 15.0;
        for (unsigned int i = 0; i < 65; i++)
        {
            railTrackZ = 15.0;
            railTrackZ = railTrackZ - 2.2 * i;
            //Rail Track
            glm::mat4 modelMatrixForContainer3 = glm::mat4(1.0f);
            glm::mat4 modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX, railTrackY, railTrackZ));
            glm::mat4 scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .075, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            //Right Track

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5+1.25, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5 + 1.25, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5 + 1.25, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            

            //Stones
            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .1, railTrackY - 0.15, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(4.0, -0.1, -2.0));

            stone.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            //middle piller


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .5, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(5.00, -0.1, -.2));

            wood.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .5, railTrackY - 0.3, railTrackZ - .8));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(5.00, -0.1, -.2));

            wood.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .5, railTrackY - 0.3, railTrackZ - 1.6));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(5.00, -0.1, -.2));

            wood.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);
        }
        railTrackX = -10.5, railTrackY = -1.45, railTrackZ = 15.0;
        for (unsigned int i = 0; i < 65; i++)
        {
            railTrackZ = 15.0;
            railTrackZ = railTrackZ - 2.2 * i;
            //Rail Track
            glm::mat4 modelMatrixForContainer3 = glm::mat4(1.0f);
            glm::mat4 modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX, railTrackY, railTrackZ));
            glm::mat4 scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .075, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            //Right Track

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5 + 1.25, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5 + 1.25, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5 + 1.25, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            railpath.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);




            //Stones
            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .1, railTrackY - 0.15, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(4.0, -0.1, -2.0));

            stone.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            //middle piller


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .5, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(5.00, -0.1, -.2));

            wood.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .5, railTrackY - 0.3, railTrackZ - .8));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(5.00, -0.1, -.2));

            wood.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .5, railTrackY - 0.3, railTrackZ - 1.6));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(5.00, -0.1, -.2));

            wood.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);
        }

        // entry counter
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 6.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(32.3f, 3.5f, 2.5f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(-16.0f, -3.0f, 33.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;

        entrance.drawCubeWithTexture(lightingShaderWithTexture, model);

        // counter maze
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.00f, 2.0f, 16.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(29.9f, 0.1f, 26.0f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(0.90f, -2.5f, 2.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;

        maze.drawCubeWithTexture(lightingShaderWithTexture, model);

        // ticket counter

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 6.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.3f, 1.5f, 0.5f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(-13.0f, -4.5f, 34.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;

        ticket.drawCubeWithTexture(lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 6.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.3f, 1.5f, 0.5f));
        moveMatrix = glm::translate(identityMatrix, glm::vec3(12-13.0f, -4.5f, 34.0f));
        model = moveMatrix * translateMatrix * scaleMatrix;

        entry.drawCubeWithTexture(lightingShaderWithTexture, model);

        if(tr == true)
            move -= 1.0f;
        if (move < -80.0f) move = 0.0f;

        if(fn == true)
            isRotate ^= 1;
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(r, g, b));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = moveMatrix * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = moveMatrix * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = moveMatrix * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = moveMatrix * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = moveMatrix * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = moveMatrix * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

}
void Table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{

    float tableY = 0.05f;
    // Top
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f + tableY, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 1.0f));
    model = moveMatrix* translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.773, 0.91, 0.059);

    // box
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.6f + tableY, 0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1, 0.0, 0.0);

    // Leg 1
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.02f, -0.46f + tableY, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
    model1 = moveMatrix * translateMatrix1 * scaleMatrix1;
    drawCube(cubeVAO, lightingShader, model1, 1.5f, 0.0f, 0.0f);


    // Leg 2
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.02f, -0.46f + tableY, 0.88f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
    model2 = moveMatrix * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, 1.5f, 0.0f, 0.0f);


    // Leg 3
    //glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(1.39f, -0.46f + tableY, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
    model1 = moveMatrix * translateMatrix1 * scaleMatrix1;
    drawCube(cubeVAO, lightingShader, model1, 1.5f, 0.0f, 0.0f);


    // Leg 4
    //glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(1.39f, -0.46f + tableY, 0.88f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
    model2 = moveMatrix * translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, model2, 1.5f, 0.0f, 0.0f);
}

void Chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    float fixLeg = 0.7f;
    float fixY = 0.1f;
    float fixYWhole = -0.08f;

    // Top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.11f, 0.0f - fixY + fixYWhole, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.07f, 0.7f));
    model = translateMatrix * scaleMatrix;
    model = moveMatrix * model;
    drawCube(cubeVAO, lightingShader, model, 0.9f, 0.3f, 0.0f);

    // Leg 1
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.13f, -0.32f + fixYWhole, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.4f * fixLeg, 0.07f));
    model = translateMatrix1 * scaleMatrix1;
    model = moveMatrix * model;
    drawCube(cubeVAO, lightingShader, model, 0.9f, 0.9f, 1.0f);

    // Leg 2
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.13f, -0.32f + fixYWhole, 0.51f));
    scaleMatrix2 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.4f * fixLeg, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);

    //// Leg 3
    //glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.76f, -0.32f + fixYWhole, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.4f * fixLeg, 0.07f));
    model1 = translateMatrix1 * scaleMatrix1;
    model1 = moveMatrix * model1;
    drawCube(cubeVAO, lightingShader, model1, 0.9f, 0.9f, 1.0f);

    // Leg 4
    //glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.76f, -0.32f + fixYWhole, 0.51f));
    scaleMatrix2 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.4f * fixLeg, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);


    //Left up 
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.17f, 0.01f - fixY + fixYWhole, 0.29f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    //drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);


    //Right up
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.39f, 0.01f - fixY + fixYWhole, 0.29f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    //drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);

    //Back support
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f, 0.08f - fixY + fixYWhole, 0.58f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.5f, 0.1f));
    model = translateMatrix * scaleMatrix;
    model = moveMatrix * model;
    drawCube(cubeVAO, lightingShader, model, 0.9f, 0.3f, 1.0f);
}
void ultaChair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    float fixLeg = 0.7f;
    float fixY = 0.1f;
    float fixYWhole = -0.08f;

    // Top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.11f, 0.3f - fixY + fixYWhole, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.07f, 0.7f));
    model = translateMatrix * scaleMatrix;
    model = moveMatrix * model;
    drawCube(cubeVAO, lightingShader, model, 0.9f, 0.3f, 0.0f);

    // Leg 1
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.13f, -0.32f + fixYWhole, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model = translateMatrix1 * scaleMatrix1;
    model = moveMatrix * model;
    drawCube(cubeVAO, lightingShader, model, 0.9f, 0.9f, 1.0f);

    // Leg 2
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.13f, -0.32f + fixYWhole, 0.51f));
    scaleMatrix2 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);

    //// Leg 3
    //glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.76f, -0.32f + fixYWhole, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model1 = translateMatrix1 * scaleMatrix1;
    model1 = moveMatrix * model1;
    drawCube(cubeVAO, lightingShader, model1, 0.9f, 0.9f, 1.0f);

    // Leg 4
    //glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.76f, -0.32f + fixYWhole, 0.51f));
    scaleMatrix2 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);


    //Left up 
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.17f, 0.01f - fixY + fixYWhole, 0.29f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    //drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);


    //Right up
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.39f, 0.01f - fixY + fixYWhole, 0.29f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    model2 = moveMatrix * model2;
    //drawCube(cubeVAO, lightingShader, model2, 0.9f, 0.9f, 1.0f);

    //Back support
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f, 0.38f - fixY + fixYWhole, 0.08f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.5f, 0.1f));
    model = translateMatrix * scaleMatrix;
    model = moveMatrix * model;
    drawCube(cubeVAO, lightingShader, model, 0.9f, 0.3f, 1.0f);
}
void SideWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f * 1.6f, 12.0f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.557f, 0.961f, 0.024f);
}
void SideWall1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f * 1.6f, 12.0f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.878f, 0.196f, 0.604f);
}
void FrontWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.3f, 1.5f * 1.6f, 0.5f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.8f, 0.9f, 0.7f);
}
void FrontWall1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.3f, 1.5f * 1.6f, 0.5f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.604f, 0.902f, 1.0f);
}
void joint(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -5.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.5f, 1.0f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.871f, 0.176f, 0.733f);
}
void Roof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.0f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.2f, 0.1f, 14.0f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.678f, 0.671f, 0.082f);
    
}
void Platform(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.25f + 0.45f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.0f, 0.55f, 160.0f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.631f, 0.643f, 0.851f);
}
void Floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.25f + 0.45f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.1f, 17.0f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.678f, 0.671f, 0.082f);
}

void BlackBoard(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    float fixY = 0.4f;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.3f, 0.2f + fixY, -3.99f));        //Frame
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.3f, 1.5f, 0.1f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.294f, 0.38f, 0.31f);
    

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.23f, 0.26f + fixY, -3.98f));        //Board
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 1.3f, 0.1f));
    model = moveMatrix * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.059f, 0.878f, 0.184f);
}
void Window(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix,unsigned int x)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+x), glm::vec3(0.0f, 1.0f, 0.0f));
    float fixY = 0.4f;


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.23f, 0.26f + fixY, -3.98f));        //Board
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.5f, 1.3f, 0.15f));
    model = moveMatrix * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.294f, 0.31f, 0.294f);
}
void Fan1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateToPivot, translateFromPivot, rotateYMatrix, scaleMatrix, model, moveModel;
    glm::vec4 translateToPivotOrg, translateFromPivotOrg;
    glm::vec3 pivot;

    //Handle
    moveModel = glm::translate(identityMatrix, glm::vec3(0.0f, 1.77f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
    model = moveMatrix * moveModel * scaleMatrix;

    drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 0.2f);

    if (isRotate)
    {
        rotateAngle_Y += fanSpeed;
        rotateAngle_Y = fmod(rotateAngle_Y, 360);
    }



    //Center
    pivot = glm::vec3(0.25, 0.25, 0.25);

    translateToPivotOrg = glm::vec4(-pivot, 0.0f);
    translateFromPivotOrg = glm::vec4(pivot, 0.0f);

    moveModel = glm::translate(identityMatrix, glm::vec3(-0.1f, 1.65f, -0.1f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.3f, 0.3f));

    translateToPivotOrg = scaleMatrix * translateToPivotOrg;
    translateFromPivotOrg = scaleMatrix * translateFromPivotOrg;
    translateToPivot = glm::translate(identityMatrix, glm::vec3(translateToPivotOrg));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(translateFromPivotOrg));

    model = moveMatrix * moveModel * translateFromPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    //model = moveModel * rotateYMatrix * scaleMatrix;
    //model =  translateFromPivot * rotateYMatrix * translateToPivot;
    drawCube(cubeVAO, lightingShader, model, 0.2f, 1.0f, 0.2f);
    //One hand

    translateToPivotOrg = glm::vec4(-pivot, 0.0f);
    translateFromPivotOrg = glm::vec4(pivot, 0.0f);

    moveModel = glm::translate(identityMatrix, glm::vec3(-0.75f, 1.67f, -0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.8f, 0.1f, 0.3f));

    translateToPivotOrg = scaleMatrix * translateToPivotOrg;
    translateFromPivotOrg = scaleMatrix * translateFromPivotOrg;
    translateToPivot = glm::translate(identityMatrix, glm::vec3(translateToPivotOrg));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(translateFromPivotOrg));

    model = moveMatrix * moveModel * translateFromPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 1.0f);

    //Second hand

    translateToPivotOrg = glm::vec4(-pivot, 0.0f);
    translateFromPivotOrg = glm::vec4(pivot, 0.0f);

    moveModel = glm::translate(identityMatrix, glm::vec3(-0.05f, 1.67f, -0.65f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.1f, 1.8f));

    translateToPivotOrg = scaleMatrix * translateToPivotOrg;
    translateFromPivotOrg = scaleMatrix * translateFromPivotOrg;
    translateToPivot = glm::translate(identityMatrix, glm::vec3(translateToPivotOrg));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(translateFromPivotOrg));

    model = moveMatrix * moveModel * translateFromPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.2f, 0.2f, 1.0f);

}

void Fan2(Shader ourShader)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateToPivot, translateFromPivot, rotateYMatrix, scaleMatrix, model, moveModel;

    //Handle
    moveModel = glm::translate(identityMatrix, glm::vec3(0.0f, 1.77f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
    model = moveModel * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("objectColor", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    if (isRotate)
    {
        rotateAngle_Y += 2.7f;
        rotateAngle_Y = fmod(rotateAngle_Y, 360);
    }


    translateToPivot = glm::translate(identityMatrix, glm::vec3(-0.25f, -0.25f, -0.25f));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.25f, 0.25f, 0.25f));

    //Another way

    float fixX = 0.0;
    float fixZ = 0.0f;

    //Center
    moveModel = glm::translate(identityMatrix, glm::vec3(-0.1f, 1.65f, -0.1f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.3f, 0.5f));
    model = moveModel * scaleMatrix * translateFromPivot * rotateYMatrix * translateToPivot;
    ourShader.setMat4("model", model);
    ourShader.setVec4("objectColor", glm::vec4(0.2f, 1.0f, 0.2f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //hand 1
    moveModel = glm::translate(identityMatrix, glm::vec3(0.0f + fixX, 1.67f, -0.05f + fixZ));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1.5f, 0.1f, 0.3f));
    model = moveModel * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("objectColor", glm::vec4(0.2f, 0.2f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //hand 2
    moveModel = glm::translate(identityMatrix, glm::vec3(0.0f + fixX, 1.67f, -0.05f + fixZ));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 0.3f));
    model = moveModel * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("objectColor", glm::vec4(0.2f, 0.2f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //hand 3
    moveModel = glm::translate(identityMatrix, glm::vec3(-0.05f + fixX, 1.67f, 0.0f + fixZ));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.1f, -1.5f));
    model = moveModel * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("objectColor", glm::vec4(0.2f, 0.2f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //hand 4
    moveModel = glm::translate(identityMatrix, glm::vec3(-0.05f + fixX, 1.67f, 0.0f + fixZ));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.1f, 1.5f));
    model = moveModel * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("objectColor", glm::vec4(0.2f, 0.2f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void bogi(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 moveMatrix, unsigned int id)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, rotateYMatrix, translateMatrix2;
    glm::vec4 color1;

    float chairZ = 0.4f;

    float fixY = 0.45f;

    float chairX = 0.05f;
    
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, i - 1.0f - chairZ));
        Chair(cubeVAO, lightingShader, moveMatrix * translateMatrix);
    }
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f-0.80f, 0.0f, i - 1.0f - chairZ));
        Chair(cubeVAO, lightingShader, moveMatrix * translateMatrix);
    }

    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f+2.0f, 0.0f, i - 1.0f - chairZ));
        Chair(cubeVAO, lightingShader, moveMatrix * translateMatrix);
    }
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + 2.80f, 0.0f, i - 1.0f - chairZ));
        Chair(cubeVAO, lightingShader, moveMatrix * translateMatrix);
    }



    //Walls
    

    if (id == 1) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.80f, -0.45f, -0.50f));
        FrontWall1(cubeVAO, lightingShader, moveMatrix * translateMatrix);     //Front

        translateMatrix = glm::translate(identityMatrix, glm::vec3(.87f, -0.45f, 13.50f));
        FrontWall1(cubeVAO, lightingShader, moveMatrix * translateMatrix);        //Back

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, -0.45f, 0.0f));
        SideWall(cubeVAO, lightingShader, moveMatrix * translateMatrix);     //Left

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -0.45f, 0.0f));
        SideWall(cubeVAO, lightingShader, moveMatrix * translateMatrix);     //Right
    }
    else {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.80f, -0.45f, -0.50f));
        FrontWall(cubeVAO, lightingShader, moveMatrix * translateMatrix);     //Front

        translateMatrix = glm::translate(identityMatrix, glm::vec3(.87f, -0.45f, 13.50f));
        FrontWall(cubeVAO, lightingShader, moveMatrix * translateMatrix);        //Back

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, -0.45f, 0.0f));
        SideWall1(cubeVAO, lightingShader, moveMatrix * translateMatrix);     //Left

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -0.45f, 0.0f));
        SideWall1(cubeVAO, lightingShader, moveMatrix * translateMatrix);     //Right
    }
    

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.90f, -0.20f, 2.0f));
    //color1 = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    Roof(cubeVAO, lightingShader, moveMatrix * translateMatrix);      //Roof

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.90f, -2.5f, 2.0f));
    //color1 = glm::vec4(0.38f, 0.3f, 0.3f, 1.0f);
    Roof(cubeVAO, lightingShader, moveMatrix * translateMatrix);    //Floor


    //BlackBoard
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, -0.5f, 0.0f));
    BlackBoard(cubeVAO, lightingShader, moveMatrix * translateMatrix);

    // Window Left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.07f, -0.5f, 8.0f));
    Window(cubeVAO, lightingShader, moveMatrix * translateMatrix , 90);

    // Window Right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.2f, -0.5f, 8.0f));
    Window(cubeVAO, lightingShader, moveMatrix * translateMatrix, 90);
    //Fan
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2f, -0.25f, 2.0f));
    Fan1(cubeVAO, lightingShader, moveMatrix * translateMatrix);

    // wheel 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -1.0f, 10.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.02f, 0.2f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.1f, 0.06f, -1.0f));
    Wheel wheel = Wheel(1.0f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), 
        glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255),
        glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);

    wheel.drawWheel(lightingShader, moveMatrix * translateMatrix2 * rotateYMatrix * translateMatrix * scaleMatrix);


    // wheel 2
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(2.6f, 0.06f, -1.0f));

    wheel.drawWheel(lightingShader, moveMatrix * translateMatrix2 * rotateYMatrix * translateMatrix * scaleMatrix);


    // wheel 3
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-1.1f, 0.06f, -13.0f));
    wheel.drawWheel(lightingShader, moveMatrix * translateMatrix2 * rotateYMatrix * translateMatrix * scaleMatrix);
    
    // wheel 4
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(2.6f, 0.06f, -13.0f));

    wheel.drawWheel(lightingShader, moveMatrix * translateMatrix2 * rotateYMatrix * translateMatrix * scaleMatrix);



}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime * 2);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }




    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }*/
    /*if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;*/
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }



    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        pointlight2.turnOn();
        // pointlight3.turnOff();
        // pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        pointlight2.turnOff();
        // pointlight3.turnOff();
        // pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        pointlight3.turnOn();
        // pointlight3.turnOff();
        // pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        pointlight3.turnOff();
        // pointlight3.turnOff();
        // pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        // pointlight3.turnOff();
        // pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        // pointlight3.turnOff();
        // pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        cout << "Point Light Off" << endl;
        pointlight1.turnOff();
        pointlight2.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();
        pointlight5.turnOff();
        pointlight6.turnOff();
        pointlight7.turnOff();
        pointlight8.turnOff();
        pointlight9.turnOff();
        pointlight10.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        cout << "Point Light On" << endl;
        pointlight1.turnOn();
        pointlight2.turnOn();
        pointlight3.turnOn();
        pointlight4.turnOn();
        pointlight5.turnOn();
        pointlight6.turnOn();
        pointlight7.turnOn();
        pointlight8.turnOn();
        pointlight9.turnOn();
        pointlight10.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            cout << "Point Light Diffuse Off" << endl;
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            pointlight5.turnDiffuseOff();
            pointlight6.turnDiffuseOff();
            pointlight7.turnDiffuseOff();
            pointlight8.turnDiffuseOff();
            pointlight9.turnDiffuseOff();
            pointlight10.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            cout << "Point Light Diffuse On" << endl;
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            pointlight5.turnDiffuseOn();
            pointlight6.turnDiffuseOn();
            pointlight7.turnDiffuseOn();
            pointlight8.turnDiffuseOn();
            pointlight9.turnDiffuseOn();
            pointlight10.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (specularToggle)
        {
            cout << "Point Light Specular Off" << endl;
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            pointlight5.turnSpecularOff();
            pointlight6.turnSpecularOff();
            pointlight7.turnSpecularOff();
            pointlight8.turnSpecularOff();
            pointlight9.turnSpecularOff();
            pointlight10.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            cout << "Point Light Specular On" << endl;
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            pointlight5.turnSpecularOn();
            pointlight6.turnSpecularOn();
            pointlight7.turnSpecularOn();
            pointlight8.turnSpecularOn();
            pointlight9.turnSpecularOn();
            pointlight10.turnSpecularOn();
            specularToggle = !specularToggle;
        }



    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        cout << "Point Light All property On" << endl;
        pointlight1.turnAmbientOn();
        pointlight2.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
        pointlight5.turnAmbientOn();
        pointlight6.turnAmbientOn();
        pointlight7.turnAmbientOn();
        pointlight8.turnAmbientOn();
        pointlight9.turnAmbientOn();
        pointlight10.turnAmbientOn();

        pointlight1.turnDiffuseOn();
        pointlight2.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
        pointlight5.turnDiffuseOn();
        pointlight6.turnDiffuseOn();
        pointlight7.turnDiffuseOn();
        pointlight8.turnDiffuseOn();
        pointlight9.turnDiffuseOn();
        pointlight10.turnDiffuseOn();

        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
        pointlight5.turnSpecularOn();
        pointlight6.turnSpecularOn();
        pointlight7.turnSpecularOn();
        pointlight8.turnSpecularOn();
        pointlight9.turnSpecularOn();
        pointlight10.turnSpecularOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        cout << "Change Color of point light" << endl;
        pointlight1.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight2.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight3.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight4.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight5.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight5.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight5.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight6.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight6.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight6.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight7.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight7.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight7.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight8.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight8.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight8.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight9.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight9.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight9.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight10.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight10.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight10.specular = glm::vec3(0.0, 1.0, 0.0);
    }

    
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        
        tr ^= 1;
        if (tr) {
            cout << "Train is Running" << endl;
        }
        else {
            cout << "Train is Stopped" << endl;
        }
        //lightingShader.setBool("dlighton", true);
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        fn ^= 1;
        if (fn) {
            cout << "Fan is Running" << endl;
        }
        else {
            cout << "Fan is Stopped" << endl;
        }
        //lightingShader.setBool("dlighton", true);
    }

}

//void dlight(Shader& lightingShader) {
//
//}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
