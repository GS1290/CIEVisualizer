#include "raylib.h"
#include "raymath.h"
#include "helper.h"


int main()
{
    // ... (InitWindow, Camera setup, etc.) ...
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - mesh generation");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Mesh myMesh = CreateColoredSquare((Vector3){0.0f, 0.0f, 0.0f}, 10);
    Model myModel = LoadModelFromMesh(myMesh); // Create a model from the mesh

    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    float rotationAngle = 90.0f;
    Vector3 position = { 1.0f, 0.0f, 0.0f };

    // If no normals are generated, you will need a shader that doesn't expect them 
    // or you can load a default material without a texture which uses the diffuse color
    // or provide a simple shader that only uses vertex colors.
    // By default, DrawModel uses an internal shader that expects vertex colors if the mesh has them.

    while (!WindowShouldClose())
    {
        // ... (UpdateCamera, etc.) ...
        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed(KEY_Z)) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                // Draw the model with its vertex colors
                // The color passed to DrawModel is a tint, use WHITE to show original vertex colors
                //DrawModel(myModel, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
                DrawMesh(myMesh, LoadMaterialDefault(), MatrixScale(1.0f, 1.0f, 1.0f));
                // Calculate transformation matrix from function parameters
                // Get transform matrix (rotation -> scale -> translation)
                Matrix matScale = MatrixScale(1.0f, 1.0f, 1.0f);
                Matrix matRotation = MatrixRotate(rotationAxis, rotationAngle*DEG2RAD);
                Matrix matTranslation = MatrixTranslate(position.x, position.y, position.z);

                Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
                DrawMesh(myMesh, LoadMaterialDefault(), matTransform);
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