#include "raylib.h"
#include "functions.h"
#define temp_count 10
#define max_temp 100
typedef float angle;

//-------------------------------------------------------------------------------------------
// function definition
//-------------------------------------------------------------------------------------------

void drawtempgraph(const int* temperature, int count, Rectangle grapharea);
void drawwinddirgraph(Vector2 position, float radius, angle direction, int pointerwith);

//-------------------------------------------------------------------------------------------
// global variables
//-------------------------------------------------------------------------------------------

Vector2 origin = {
     .x = 0 ,
     .y = 0 ,
};

//-------------------------------------------------------------------------------------------
// Program main entry point
//-------------------------------------------------------------------------------------------
int main(void)
{        
    
         //----------------------------------------------------------------------------------
        // Initialization
       //------------------------------------------------------------------------------------

    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int x = 0;
    angle inputdir = 0;

    int temperature[temp_count] = {0,10,20,30,40,50,60,70,80,100};

    Rectangle temp_grapharea = {180,100,800,400};
    Vector2 wind_grapharea = {1500,300};
    
    SetDir();

    InitWindow(screenWidth, screenHeight, "weather station GUI");
    Texture2D texture = LoadTexture("..\\..\\..\\..\\..\\..\\..\\src\\textures\\TUS-logo-909091323.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


         //----------------------------------------------------------------------------------
        // Main game loop
       //------------------------------------------------------------------------------------


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
         //----------------------------------------------------------------------------------
        // Update
       //------------------------------------------------------------------------------------
        
        
        x++;
        if (x == 60) {

            for (int i = temp_count; i > 0; i--) {
               
                
                    temperature[i] = temperature[i - 1];
              
            }

            temperature[0] = GetRandomValue(60, 70);
            x = 0;
        }
        
        if (inputdir == 360) {
            inputdir = 0;
        }
        inputdir = inputdir+1;


         //----------------------------------------------------------------------------------
        // Draw
       //------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, RAYWHITE);
        drawtempgraph(temperature, temp_count, temp_grapharea);
        drawwinddirgraph(wind_grapharea, 190, inputdir, 10);


        EndDrawing();
        
    }
         //----------------------------------------------------------------------------------
        // De-Initialization
       //------------------------------------------------------------------------------------
    UnloadTexture(texture);
    CloseWindow();        // Close window and OpenGL context
    return 0;
}




void drawwinddirgraph(Vector2 position, float radius, angle direction, int pointerwith) {

    direction = direction - 90;
    DrawCircle(position.x, position.y, radius+10, DARKBLUE);
    DrawCircle(position.x, position.y, radius, GRAY);
    DrawCircleSector(position, radius, direction - pointerwith / 2, direction + pointerwith / 2, 1, RED);
    DrawCircle(position.x, position.y, radius-70, DARKBLUE);
    DrawText("N", position.x-10, position.y - radius + 75, 30, BLACK);
    DrawText("W", position.x - radius + 75, position.y -10, 30, BLACK);
    DrawText("S", position.x - 10, position.y + radius - 100, 30, BLACK);
    DrawText("E", position.x + radius - 95, position.y - 10, 30, BLACK);
    



}




void drawtempgraph(const int* temperature, int count, Rectangle grapharea)
{
    float graphHeight = grapharea.height;
    float graphWith = grapharea.width;
    float withspaceing = graphWith / (count-1);
    float heightspaceing = graphHeight / max_temp;
    float fontsize = 20;

    DrawRectangleRec(grapharea, LIGHTGRAY);

    for (int i = 0; i < count; i++) {
        Vector2 endpoint = {
            .x = grapharea.x + withspaceing * (i+1),
            .y = grapharea.y + graphHeight - (temperature[i+1]*heightspaceing) ,
        };

        Vector2 startpoint = {
            .x = grapharea.x + withspaceing * (i),
            .y = grapharea.y + graphHeight - (temperature[i] * heightspaceing) ,
        };

        Vector2 axislabel = {
            .x = grapharea.x + grapharea.width/2 - fontsize*  4,
            .y = grapharea.y + grapharea.height + fontsize * 2.5,
        };

        Vector2 axislabel2 = {
            .x = grapharea.x - fontsize*3,
            .y = grapharea.y + graphHeight*16/20,
        };



        DrawCircle(startpoint.x, startpoint.y, 5, DARKBLUE);
        if (i != 9) {
            DrawLineV(startpoint, endpoint, BLACK);
        }


        for (int i = 0; i < count; i++) {
            float x = grapharea.x + (withspaceing * (i)) -3;
            float y = grapharea.y + grapharea.height + fontsize;

            DrawText(TextFormat("%d",i ), x, y, fontsize, BLUE);

        }

        for (int i = 0; i <= count; i++) {
            float x = grapharea.x-30;
            float y = grapharea.y - 10 + (graphHeight/count)*i;

            DrawText(TextFormat("%d", (100-i*10)), x, y, fontsize, BLUE);

        }

            

            DrawRectangleLines(grapharea.x, grapharea.y, grapharea.width, grapharea.height, BLACK);
            
            DrawLine( grapharea.x-10 , grapharea.y+ grapharea.height+10, grapharea.x+grapharea.width+10, grapharea.y + grapharea.height + 10, BLUE);

            DrawTextPro(GetFontDefault(), "time in seconds", axislabel, origin , 0, fontsize+2, 4 , BLACK);
           
            DrawTextPro(GetFontDefault(), "temp in deg c", axislabel2, origin, 270, fontsize+2, 4, BLACK);
         

    }



}