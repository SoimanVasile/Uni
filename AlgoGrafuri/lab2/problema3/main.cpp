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
    for (size_t i=0; i<labirint.size(); i++){
        for (size_t j=0; j<labirint[i].size(); j++){
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
    
    size_t index=0;
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
            if (new_y<0 || new_y>=labirint_rezolvare[new_x].size())
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
    if (start.first == -1 || finish.first == -1){
        std::cout<<"Labirintul nu contine 'S' sau 'F'!\n";
        return 1;
    }
    vector<item> queue = maze_solver(labirint, start, finish);
    if (queue.empty()){
        std::cout<<"Nu exista solutie!\n";
        return 1;
    }
    int solver = queue.size()-1;
    while (queue[solver].parent_cell.first != -1 && queue[solver].parent_cell.second != -1){
        labirint[queue[solver].cell.first][queue[solver].cell.second] = '#';
        for (int k = solver - 1; k >= 0; k--){
            if (queue[k].cell.first == queue[solver].parent_cell.first &&
                queue[k].cell.second == queue[solver].parent_cell.second){
                solver = k;
                break;
            }
        }
    }
    labirint[start.first][start.second] = 'S';
    labirint[finish.first][finish.second] = 'F';
    std::cout<<"\nSolutie:\n";
    print_labirint_t(labirint);
    return 0;
}

