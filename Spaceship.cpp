#include "Print_star.h"
#include "Remove_star.h"
#include <cstdlib>
#include <limits.h>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>
using namespace std;
int myRand(int fromA, int toB) {
  if (fromA > toB)
    return myRand(toB, fromA);
  int d = toB - fromA;
  int r = rand() % (d + 1);
  return r + fromA;
}
struct bullet {
  int y;
  int x;
  int tick;
  int check;
};
struct star {
  int y = 0;
  int x = 0;
  star *next = 0;
};
vector<string> spaceship{"           \\\\\\_____", "        ###[==_____>",
                         "           ///     "};
vector<string> number_of_spaces{"        ", "            ", "   "};
void remove_space_ship(int &x, int &y) {
  int Y = y;
  int X = x;
  move(Y, X);
  for (int i = 0; i < number_of_spaces.size(); i++) {
    if (i == 1) {
      X -= 3;
    }
    if (i == 2) {
      X += 3;
    }
    printw("%s\n", number_of_spaces[0].c_str());
    Y++;
    move(Y, X);
  }
  move(y, x);
}
void move_space_ship(int &x, int &y, int key) {
  if (key == 115) {
    remove_space_ship(x, y);
    // move down
    y++;
    move(y, x);
    int Y = y;
    for (int i = 0; i < spaceship.size(); i++) {
      printw("%s\n", spaceship[i].c_str());
      Y++;
      move(Y, x);
    }
    return;
  }
  if (key == 119) {
    remove_space_ship(x, y);
    // move up
    y--;
    move(y, x);
    int Y = y;
    for (int i = 0; i < spaceship.size(); i++) {
      printw("%s\n", spaceship[i].c_str());
      Y++;
      move(Y, x);
    }
    return;
  }
  if (key == 100) {
    remove_space_ship(x, y);
    // move right
    x++;
    int Y = y;
    move(y, x);
    for (int i = 0; i < spaceship.size(); i++) {
      printw("%s\n", spaceship[i].c_str());
      Y++;
      move(Y, x);
    }
    return;
  }
  if (key == 97) {
    remove_space_ship(x, y);
    // move left
    x--;
    int Y = y;
    move(y, x);
    for (int i = 0; i < spaceship.size(); i++) {
      printw("%s\n", spaceship[i].c_str());
      Y++;
      move(Y, x);
    }
    return;
  }
}
void print_main_menu() {
  unordered_map<int, vector<int>> map;
  move(6, 70);
  printw("000000  000000   000000  000000  000000");
  move(7, 70);
  printw("0       0    0   0    0  0       0     ");
  move(8, 70);
  printw("000000  000000   000000  0       000000");
  move(9, 70);
  printw("     0  0        0    0  0       0     ");
  move(10, 70);
  printw("000000  0        0    0  000000  000000");
  move(12, 84);
  printw("________");
  move(13, 84);
  printw("|      |");
  move(14, 84);
  printw("| play |");
  move(15, 84);
  printw("|______|");
  move(14, 88);
  while (getch() != 10) {
  }
  clear();
}
void print_helth_bar() {
  move(0, 0);
  printw("   _ _");
  move(1, 0);
  printw(" /  V  \\");
  move(2, 0);
  printw(" |     |");
  move(3, 0);
  printw("  \\   /");
  move(4, 0);
  printw("   \\ /");
  move(5, 0);
  printw("    *");
}
bullet *create_memory_for_bullet() {
  bullet *ptr = (bullet *)malloc(sizeof(bullet));
  return ptr;
}
star *create_memory_for_star(int y, int x) {
  star *ptr = (star *)malloc(sizeof(bullet));
  ptr->y = y;
  ptr->x = x;
  return ptr;
}
void shoot(bullet *ptr, int getch, int y, int x) {
  if (ptr->tick == 199) {
    ptr->check = 0;
  }
  if (ptr->check == 0 && getch == 32) {
    ptr->y = y + 1;
    ptr->x = x + 21;
    ptr->tick = 0;
    ptr->check = 1;
  }
  if (ptr->check == 1) {
    ptr->tick++;
    move(ptr->y, ptr->x);
    if (ptr->tick != 198) {
      printw("-");
    }
    move(ptr->y, ptr->x - 1);
    printw(" ");
  }
  ptr->x++;
}

int main() {
  initscr();
  print_main_menu();
  star *star_ptr = create_memory_for_star(myRand(5, 50), myRand(20, 200));
  star *sec_star_ptr = star_ptr;
  for (int i = 0; i < 10; i++) {
    star_ptr->next = create_memory_for_star(myRand(5, 50), myRand(20, 200));
    star_ptr = star_ptr->next;
  }
  star_ptr = sec_star_ptr;
  bullet *bullet_ptr = create_memory_for_bullet();
  bullet_ptr->check = 0;
  int count = 0;
  auto x = 0;
  auto y = 0;
  int x_star = 99;
  int y_star = 5;
  int check_two = 0;
  move(y, x);
  for (int i = 0; i < spaceship.size(); i++) {
    printw("%s\n", spaceship[i].c_str());
  }
  nodelay(stdscr, true);
  for (;;) {
    if (sec_star_ptr->x > -1) {
      sec_star_ptr->x--;
      remove_star(sec_star_ptr->x + 1, sec_star_ptr->y);
      if (sec_star_ptr->x != -1) {
        print_star(sec_star_ptr->x, sec_star_ptr->y);
      }
    } else {
      sec_star_ptr->x = myRand(20, 200);
    }
    if(sec_star_ptr->next != NULL){
      sec_star_ptr = sec_star_ptr->next;
    } else {
      sec_star_ptr = star_ptr;
    }
    move(0, 0);
    int b = getch();
    // making it shoot
    usleep(4999);
    shoot(bullet_ptr, b, y, x);
    // end making it shoot
    if (b == 27) {
      clear();
      print_main_menu();
      move(y, x);
      int Y = y;
      for (int i = 0; i < spaceship.size(); i++) {
        printw("%s\n", spaceship[i].c_str());
        Y++;
        move(Y, x);
      }
    }
    move_space_ship(x, y, b);
  }
}
