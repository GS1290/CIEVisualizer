#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "helper.h"

Mesh CreateColoredSquare(Vector3 norm, int gridSize)
{
    Mesh mesh = {0};
    mesh.vertexCount = 6*pow(gridSize, 2);
    mesh.triangleCount = 2*pow(gridSize, 2);

    // Allocate memory for vertices (x, y, z for each vertex)
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    // Allocate memory for colors (r, g, b, a for each vertex)
    mesh.colors = (unsigned char*)MemAlloc(mesh.vertexCount * 4 * sizeof(unsigned char));
    
    // Check if allocation was successful (optional but good practice)
    if (mesh.vertices == NULL || mesh.colors == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to allocate mesh memory");
        // Free allocated memory if one fails
        if (mesh.vertices) MemFree(mesh.vertices);
        if (mesh.colors) MemFree(mesh.colors);
        return mesh; // return empty mesh
    }

    float xstep = 1.0f/gridSize;
    float ystep = 1.0f/gridSize;
    float zstep = 0.0f/gridSize;

    Vector3 vertices[4] = { 0 }; // Required to store face vertices
    vertices[2] = (Vector3){ 0, 0, 0 };
    vertices[3] = (Vector3){ 0, ystep, 0 };
    int vertexi = 0;
    int colori = 0;

    for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                vertices[0] = vertices[2]; // Shift in x axis to set up vertices for next face
                vertices[1] = vertices[3];
                vertices[2] = (Vector3){ vertices[2].x + xstep, vertices[2].y, vertices[2].z }; // Rotation matrix around y axis
                vertices[3] = (Vector3){ vertices[3].x + xstep, vertices[3].y, vertices[3].z };

                // Define vertex positions
                mesh.vertices[vertexi++] = vertices[0].x;
                mesh.vertices[vertexi++] = vertices[0].y;
                mesh.vertices[vertexi++] = vertices[0].z;   // Bottom-left
                mesh.colors[colori++] = vertices[0].x*255;
                mesh.colors[colori++] = vertices[0].y*255;
                mesh.colors[colori++] = vertices[0].z*255;
                mesh.colors[colori++] = 255;   // Red

                mesh.vertices[vertexi++] = vertices[2].x;
                mesh.vertices[vertexi++] = vertices[2].y;
                mesh.vertices[vertexi++] = vertices[2].z; // Top-left
                mesh.colors[colori++] = vertices[2].x*255;
                mesh.colors[colori++] = vertices[2].y*255;
                mesh.colors[colori++] = vertices[2].z*255;
                mesh.colors[colori++] = 255;   // Red

                mesh.vertices[vertexi++] = vertices[1].x;
                mesh.vertices[vertexi++] = vertices[1].y;
                mesh.vertices[vertexi++] = vertices[1].z;  // Bottom-right
                mesh.colors[colori++] = vertices[1].x*255;
                mesh.colors[colori++] = vertices[1].y*255;
                mesh.colors[colori++] = vertices[1].z*255;
                mesh.colors[colori++] = 255;   // Red

                mesh.vertices[vertexi++] = vertices[1].x;
                mesh.vertices[vertexi++] = vertices[1].y;
                mesh.vertices[vertexi++] = vertices[1].z;   // Top-left
                mesh.colors[colori++] = vertices[1].x*255;
                mesh.colors[colori++] = vertices[1].y*255;
                mesh.colors[colori++] = vertices[1].z*255;
                mesh.colors[colori++] = 255;   // Red

                mesh.vertices[vertexi++] = vertices[2].x;
                mesh.vertices[vertexi++] = vertices[2].y;
                mesh.vertices[vertexi++] = vertices[2].z; // Bottom-right
                mesh.colors[colori++] = vertices[2].x*255;
                mesh.colors[colori++] = vertices[2].y*255;
                mesh.colors[colori++] = vertices[2].z*255;
                mesh.colors[colori++] = 255;   // Red

                mesh.vertices[vertexi++] = vertices[3].x;
                mesh.vertices[vertexi++] = vertices[3].y;
                mesh.vertices[vertexi++] = vertices[3].z;  // Top-right
                mesh.colors[colori++] = vertices[3].x*255;
                mesh.colors[colori++] = vertices[3].y*255;
                mesh.colors[colori++] = vertices[3].z*255;
                mesh.colors[colori++] = 255;   // Red
                
            }

            vertices[2] = (Vector3){ 0.0f, vertices[2].y+ystep, vertices[2].z }; // Shift in y axis for next face
            vertices[3] = (Vector3){ 0.0f, vertices[3].y+ystep, vertices[3].z }; 
        }

    printf("vertex count = %d\n", vertexi);
    printf("color count = %d\n", colori);

    // Upload the mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh CreateColoredTriangle()
{
    Mesh mesh = { 0 };
    mesh.vertexCount = 3;
    mesh.triangleCount = 1;

    // Allocate memory for vertices (x, y, z for each vertex)
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    // Allocate memory for colors (r, g, b, a for each vertex)
    mesh.colors = (unsigned char*)MemAlloc(mesh.vertexCount * 4 * sizeof(unsigned char));
    
    // Check if allocation was successful (optional but good practice)
    if (mesh.vertices == NULL || mesh.colors == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to allocate mesh memory");
        // Free allocated memory if one fails
        if (mesh.vertices) MemFree(mesh.vertices);
        if (mesh.colors) MemFree(mesh.colors);
        return mesh; // return empty mesh
    }

    // Define vertex positions
    mesh.vertices[0] = 0.0f; mesh.vertices[1] = 1.0f; mesh.vertices[2] = 0.0f;   // Top
    mesh.vertices[3] = -1.0f; mesh.vertices[4] = -1.0f; mesh.vertices[5] = 0.0f; // Bottom-left
    mesh.vertices[6] = 1.0f; mesh.vertices[7] = -1.0f; mesh.vertices[8] = 0.0f;  // Bottom-right

    // Define vertex colors (RGBA: 0-255)
    mesh.colors[0] = 255; mesh.colors[1] = 0; mesh.colors[2] = 0; mesh.colors[3] = 255;   // Red
    mesh.colors[4] = 0; mesh.colors[5] = 255; mesh.colors[6] = 0; mesh.colors[7] = 255;   // Green
    mesh.colors[8] = 0; mesh.colors[9] = 0; mesh.colors[10] = 255; mesh.colors[11] = 255; // Blue

    // You may also want to generate normals for proper lighting if you plan to use lights
    // GenMeshNormals(&mesh); 

    // Upload the mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}