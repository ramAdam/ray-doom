// #include <vector>
#include "raylib-cpp.hpp"
#include "Entity/Player.hpp"

const int gridWidth = 20;
const int gridHeight = 20;

struct line
{
    Vector2 pointA;
    Vector2 pointB;
};
enum class DrawingMode
{
    LINE,
    POINT
};

std::vector<line> lines;

Vector2 SnapToGrid(Vector2 point)
{
    // Snap the point to the nearest grid point
    return {
        static_cast<float>(static_cast<int>((point.x + GetScreenWidth() / (gridWidth * 2)) / (GetScreenWidth() / gridWidth)) * (GetScreenWidth() / gridWidth)),
        static_cast<float>(static_cast<int>((point.y + GetScreenHeight() / (gridHeight * 2)) / (GetScreenHeight() / gridHeight)) * (GetScreenHeight() / gridHeight))};
}

void DrawLines(std::vector<line> lines)
{
    for (auto &line : lines)
    {
        DrawCircle(line.pointA.x, line.pointA.y, 3.0f, GREEN);
        DrawLineEx(line.pointA, line.pointB, 2.0f, BLUE);
    }
}

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "Grid Points Example");

    SetTargetFPS(60);

    Vector2 pointA = {-1, -1}; // Initialize point A
    Vector2 pointB = {-1, -1}; // Initialize point B
    bool drawingLine = false;  // Flag to indicate if drawing line is in progress

    // Main game loop
    while (!window.ShouldClose())
    {
        // Input handling
        if (IsKeyPressed(KEY_SPACE))
        {
            if (!drawingLine)
            {
                pointA = SnapToGrid(GetMousePosition()); // Snap to grid for Point A
                drawingLine = true;                      // Start drawing line
            }
            else
            {
                pointB = SnapToGrid(GetMousePosition()); // Snap to grid for Point B
                drawingLine = false;                     // Stop drawing line
            }
        }

        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            // Draw 2D grid
            for (int x = 0; x <= screenWidth; x += screenWidth / gridWidth)
            {
                for (int y = 0; y <= screenHeight; y += screenHeight / gridHeight)
                {
                    DrawCircle(x, y, 2.0f, LIGHTGRAY); // Draw grid points
                }
            }

            // Draw line if drawing is in progress
            if (drawingLine && pointA.x != -1 && pointA.y != -1)
            {
                Vector2 snappedPoint = SnapToGrid(GetMousePosition());
                DrawLineEx(pointA, snappedPoint, 2.0f, RED); // Draw line from Point A to current mouse position
            }

            // Draw confirmed points and lines
            if (pointB.x != -1 && pointB.y != -1)
            {
                DrawCircle(pointB.x, pointB.y, 3.0f, BLUE); // Draw confirmed Point B
                DrawLineEx(pointA, pointB, 2.0f, BLUE);     // Draw line from Point A to Point B
                lines.push_back({pointA, pointB});          // Add line to lines vector
                pointA = pointB;
                pointB = {-1, -1};
                drawingLine = true;
            }

            DrawLines(lines); // Draw all lines

            DrawCircle(SnapToGrid(GetMousePosition()).x, SnapToGrid(GetMousePosition()).y, 3.0f, BLACK); // Draw current mouse position snapped to grid
        }
        EndDrawing();
    }

    return 0;
}