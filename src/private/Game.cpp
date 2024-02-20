// #include <vector>
#include "raylib-cpp.hpp"
#include "Entity/Player.hpp"

struct Line
{
    Vector2 start;
    Vector2 end;
};

std::vector<Line> lines;
std::vector<std::vector<Vector3>> sectors; // V

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "Doom Level Editor");

    Camera camera = {
        {5.0f, 5.0f, 5.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        45.0f,
        CAMERA_PERSPECTIVE};

    // Main game loop
    while (!window.ShouldClose())
    {
        // Update

        // Input handling to draw lines
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Add new line
            lines.push_back({GetMousePosition(), GetMousePosition()});
        }
        else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            // Update last line
            lines.back().end = GetMousePosition();
        }

        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            // Draw 2D grid
            // Draw 2D lines
            for (const auto &line : lines)
            {
                DrawLineEx(line.start, line.end, 2.0f, RED);
            }

            BeginMode3D(camera);
            {
                DrawGrid(10, 1.0f);

                // Draw 3D sectors and walls
                for (const auto &sector : sectors)
                {
                    // Draw sector
                    if (sector.size() > 2)
                    {
                        std::vector<Vector2> sector2D;
                        for (const auto &vertex : sector)
                        {
                            sector2D.push_back({vertex.x, vertex.z}); // Convert Vector3 to Vector2
                        }
                        DrawTriangleFan(&sector2D[0], sector2D.size(), Fade(GREEN, 0.3f));
                    }
                    // Draw walls
                    for (size_t i = 0; i < sector.size(); ++i)
                    {
                        Vector3 start3D = {sector[i].x, 0.0f, sector[i].z};
                        Vector3 end3D = {sector[(i + 1) % sector.size()].x, 0.0f, sector[(i + 1) % sector.size()].z};
                        DrawLine3D(start3D, end3D, DARKGREEN);
                    }
                }
            }
            EndMode3D();

            // Draw UI
        }
        EndDrawing();
    }

    return 0;
}
