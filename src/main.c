#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include "helper.h"

#define GLSL_VERSION            330

#define C_GLSL_INCLUDE
#include "rgb.vs"
#include "rgb.fs"


int main(void)
{
    // ... (InitWindow, Camera setup, etc.) ...
    const int screenWidth = 800;
    const int screenHeight = 450;
    bool xyYSpace = false;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - mesh generation");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    //Shader shader = LoadShader(TextFormat("src/resources/rgb.vs"), TextFormat("src/resources/rgb.fs"));
    Shader shader = LoadShaderFromMemory(rgb_vs_src, rgb_fs_src);
    Material material = LoadMaterialDefault();
    material.shader = shader;

    float time = 0.0f;
    int timeLoc = GetShaderLocation(shader, "uTime");
    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    Mesh* myMeshes = CreateRGBCube(10);
    Mesh myMesh = CreateColoredSquare(10);
    Model myModel = LoadModelFromMesh(myMesh); // Create a model from the mesh

    // If no normals are generated, you will need a shader that doesn't expect them 
    // or you can load a default material without a texture which uses the diffuse color
    // or provide a simple shader that only uses vertex colors.
    // By default, DrawModel uses an internal shader that expects vertex colors if the mesh has them.

    //DisableCursor();
    while (!WindowShouldClose())
    {
        // ... (UpdateCamera, etc.) ...
        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed(KEY_Z)) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (IsKeyPressed(KEY_R)) xyYSpace = !xyYSpace;
        time = (float)GetTime();
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground((Color){55, 55, 55, 255});
            BeginMode3D(camera);
                // --- Disable Culling for this draw call ---
                rlDisableBackfaceCulling();

                // Draw the model with its vertex colors
                // The color passed to DrawModel is a tint, use WHITE to show original vertex colors
                //DrawModel(myModel, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);


                // Activate our custom shader to be applied on next shapes/textures drawings
                //BeginShaderMode(shader);
                if (xyYSpace)
                    for(int i=0; i<6; i++) DrawMesh(myMeshes[i], material, MatrixScale(1.0f, 1.0f, 1.0f));
                else for(int i=0; i<6; i++) DrawMesh(myMeshes[i], LoadMaterialDefault(), MatrixScale(1.0f, 1.0f, 1.0f));

                
                // Activate our default shader for next drawings
                //EndShaderMode();
                

                // Calculate transformation matrix from function parameters
                // Get transform matrix (rotation -> scale -> translation)
                // Matrix matScale = MatrixScale(1.0f, 1.0f, 1.0f);
                // Matrix matRotation = MatrixRotate(rotationAxis, rotationAngle*DEG2RAD);
                // Matrix matTranslation = MatrixTranslate(position.x, position.y, position.z);

                // Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
                // DrawMesh(myMesh, LoadMaterialDefault(), matTransform);

                DrawGrid(10, 1.0f);

            EndMode3D();
        // ... (DrawFPS, EndDrawing, etc.) ...
        EndDrawing();
    }
    
    // De-Initialization
    UnloadModel(myModel); // Unloads mesh data internally
    CloseWindow();
    return 0;
}