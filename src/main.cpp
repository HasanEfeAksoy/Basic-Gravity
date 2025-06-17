#include "../include/entity.h"


int main()
{
    GLFWwindow* window = nullptr;
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    std::vector<Entity*> objects;


    Entity* mouseEntity = new Entity(0.0, 0.0, 0.0, MOUSEENTITYRADIUS, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
    objects.push_back(mouseEntity);

    for (int i = 0; i < COUNT; i++) {
        Entity* obj = new Entity(0.0, 0.0);
        objects.push_back(obj);
    }



    while (!glfwWindowShouldClose(window))
    {   
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            xpos = xpos - WIDTH / 2;
            ypos = HEIGHT / 2 - ypos;

            mouseEntity->x = xpos;
            mouseEntity->y = ypos;

            mouseEntity->mass = MOUSEENTITYMASS;
            mouseEntity->radius = MOUSEENTITYRADIUS;
        }
        else {
            mouseEntity->mass = 0.0;
            mouseEntity->radius = 0.0;
        }




        for (int i = 0; i < objects.size(); i++) {
            if (i >= objects.size()) break;

            objects[i]->tick(objects);

            for (int j = 0; j < objects.size(); j++) {
                if (i >= objects.size() || j >= objects.size()) break;

                Entity* first = objects[i];
                Entity* second = objects[j];

                if (first == second) continue;

                double dist_x = second->x - first->x;
                double dist_y = second->y - first->y;
                double distance = sqrt(dist_x * dist_x + dist_y * dist_y);

                if (distance <= first->radius + second->radius) {
                    double m1 = first->mass;
                    double m2 = second->mass;
                    double vx1 = first->vel_x;
                    double vy1 = first->vel_y;
                    double vx2 = second->vel_x;
                    double vy2 = second->vel_y;

                    double vxall = (m1 * vx1 + m2 * vx2) / (m1 + m2);
                    double vyall = (m1 * vy1 + m2 * vy2) / (m1 + m2);


                    if (first->density > second->density || first == mouseEntity) {
                        first->vel_x = vxall;
                        first->vel_y = vyall;
                        first->radius = cbrt(first->radius * first->radius * first->radius + second->radius * second->radius * second->radius);
                        first->mass += second->mass;

                        objects.erase(objects.begin() + j);
                        delete second;

                        if (j < i) i--;
                        j--;
                    }
                    else {
                        second->vel_x = vxall;
                        second->vel_y = vyall;
                        second->radius = cbrt(second->radius * second->radius * second->radius + first->radius * first->radius * first->radius);
                        second->mass += first->mass;

                        objects.erase(objects.begin() + i);
                        delete first;

                        i--;
                        break;
                    }
                }
            }
        }





        

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwTerminate();
    return 0;
}