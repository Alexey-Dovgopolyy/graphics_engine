#include "Graphics.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ManagersProvider.h"
#include "Camera.h"
#include "Time.h"
#include "ShadowMapRenderer.h"

#include "Vertex.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

#include <iostream>

bool Graphics::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);

    return true;
}

void Graphics::beforeUpdate()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);
}

void Graphics::afterUpdate()
{
    Window* window = ManagersProvider::getInstance().getWindow();
    window->swapButters();
    glfwPollEvents();
}

void Graphics::cleanup()
{
    glfwTerminate();
}

void Graphics::beforeDrawOutlinedObject()
{
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
}

void Graphics::beforeDrawOutline()
{
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
}

void Graphics::afterDrawOutline()
{
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}

void Graphics::initMesh(Mesh& mesh)
{
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    const std::vector<Vertex>& vertices = mesh.getVertices();
    const std::vector<unsigned int>& indices = mesh.getIndices();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    mesh.setVAO(VAO);
    mesh.setVBO(VBO);
    mesh.setEBO(EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

void Graphics::drawMesh(Mesh& mesh, Shader& shader)
{
    const std::vector<Texture>& textures = mesh.getTextures();
    const std::vector<unsigned int>& indices = mesh.getIndices();
    unsigned int VAO = mesh.getVAO();

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

        std::string number;
        std::string name = textures[i].type;

        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        std::string locationStr = "material." + name + number;
        shader.setInt(locationStr.c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    ShadowMapRenderer* shadowRenderer = ManagersProvider::getInstance().getShadowRenderer();
    unsigned int depthMap = shadowRenderer->getDepthMap();
    GEMat4x4 lightSpaceMatrix = shadowRenderer->getLightSpaceMatrix();
    shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    
    shader.setInt("shadowMap", textures.size());
    glActiveTexture(GL_TEXTURE0 + textures.size());
    glBindTexture(GL_TEXTURE_2D, depthMap);

    shader.setFloat("material.shininess", 32.f); // TODO do not hardcode

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Graphics::drawMeshShadow(Mesh& mesh)
{
    unsigned int VAO = mesh.getVAO();
    const std::vector<unsigned int>& indices = mesh.getIndices();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Graphics::drawDebugShadow(Shader& shader)
{
    static unsigned int quadVAO = 0;
    static unsigned int quadVBO;

    ShadowMapRenderer* shadowRenderer = ManagersProvider::getInstance().getShadowRenderer();
    unsigned int depthMap = shadowRenderer->getDepthMap();
    shader.setInt("depthMap", 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
