#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

using std::vector;
typedef vector<std::string> labirint_t;

typedef struct{
        std::pair<int, int> cell;
        std::pair<int, int> parent_cell;
    } item;
labirint_t citire_labirint(std::string file_path){

    std::ifstream fin(file_path);

    if (!fin.is_open()){
        std::cout<<"Couldnt open the file";
        exit(1);
    }


    labirint_t labirint;
    std::string linie;
    while (std::getline(fin, linie)){
        labirint.push_back(linie);
    }

    fin.close();

    return labirint;
}

std::pair<int, int> get_the_position_of_char(labirint_t labirint, char character){
    for (int i=0; i<labirint.size(); i++){
        for (int j=0; j<labirint[i].size(); j++){
            if (labirint[i][j] == character)
                return {i, j};
        }
    }

    return {-1, -1};
}

vector<item> maze_solver(labirint_t labirint, std::pair<int, int> start_position, std::pair<int, int> finish_position){
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};

    labirint_t labirint_rezolvare=labirint;
    
    int index=0;
    vector<item> queue;
    queue.push_back({{start_position.first, start_position.second}, {-1, -1}});
    labirint_rezolvare[start_position.first][start_position.second] = '9';
    while (index<queue.size()){
        int x = queue[index].cell.first;
        int y = queue[index].cell.second;
        for (int i=0; i<4; i++){
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (new_x<0 || new_x>=labirint_rezolvare.size())
                continue;
            if (new_y<0 || new_y>=labirint_rezolvare[1].size())
                continue;
            if (new_x == finish_position.first && new_y == finish_position.second){
                queue.push_back({{new_x, new_y}, {x, y}});
                return queue;
            }
            if (labirint_rezolvare[new_x][new_y] == ' '){
                queue.push_back({{new_x, new_y}, {x, y}});
                labirint_rezolvare[new_x][new_y] = '9';
            }
        }
        index++;
    }

    return {};
}

void print_labirint_t(labirint_t labirint){
    for (auto line: labirint){
            std::cout<<line<<"\n";
    }
}
int main(int argc, char** argv){
    
    if (argc!=2){
        std::cout<<"Trebuie sa dai un fisier de intrare";
        return 1;
    }

    labirint_t labirint = citire_labirint(argv[1]);
    print_labirint_t(labirint);
    std::pair<int, int> start = get_the_position_of_char(labirint, 'S');
    std::pair<int, int> finish = get_the_position_of_char(labirint, 'F');
    vector<item> queue = maze_solver(labirint, start, finish);
    int current = queue.size()-1;
    int solver = current;
    while (queue[solver].parent_cell.first !=-1 && queue[solver].parent_cell.second != -1){
        int x = queue[current].cell.first;
        int y = queue[current].cell.second;
        labirint[queue[solver].cell.first][queue[solver].cell.second] = '#';
        if (x == queue[solver].parent_cell.first && y == queue[solver].parent_cell.second){
            solver = current;
        }
        current--;
    }
    print_labirint_t(labirint);
    return 0;
}

