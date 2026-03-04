#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void menu(){
  int fd = open("menu.txt", O_RDONLY);

  if (fd <0){
    printf ("Failed to open the file");
    return;
  }
  
  int rd = 0;
  char buffer[200];
  while ((rd = read(fd, buffer, 200))){
    buffer[rd] = '\0';
    printf("%s\n", buffer);
  }
}

size_t** pascal_triangle(size_t number_of_lines){
  size_t** triangle;
  triangle = (size_t**)(malloc(number_of_lines * sizeof(size_t*)));
  
  for (size_t i=0; i<number_of_lines; i++){
    triangle[i] = (size_t*)malloc((i+1) * sizeof(size_t));
    if (i==0){ triangle[i][i] = 1; continue;}
    for (size_t j=0; j<=i; j++){
      if (j==0) {triangle[i][j] = 1; continue;}
      if (j==i) {triangle[i][j] = 1; continue;}
      triangle[i][j] = triangle[i-1][j]+triangle[i-1][j-1];
    }
  }

  return triangle;
}

int biggest_number_width(size_t** triangle, size_t number_of_lines){

  size_t max_val = triangle[number_of_lines-1][(number_of_lines-1)/2];
  int cell_width=0;
  size_t temp = max_val;
  while (temp!=0){temp/=10; cell_width+=1;}
  if (cell_width == 0){cell_width = 1;};
  return cell_width;
}

void print_triangle(size_t** triangle, size_t number_of_lines){
  if (number_of_lines == 0){
    return;
  }
  
  int cell_width = biggest_number_width(triangle, number_of_lines);

  for (size_t i=0; i<number_of_lines; i++){
    printf("%*zu", (int)((number_of_lines-i+1)*((cell_width/2)+1)), triangle[i][0]);
    for (size_t j=1; j<=i; j++){
      printf(" %*zu", cell_width, triangle[i][j]);
    }
    printf("\n");
  }
}

void free_triangle(size_t** triangle, size_t number_of_lines){
          for (size_t i=0; i<number_of_lines; i++){
          free(triangle[i]);
        }
        free(triangle);

}

void generate_the_pascal_triangle(){
        size_t number_of_lines;
        printf("Cate linii: ");
        scanf("%zu", &number_of_lines);
        size_t** triangle = pascal_triangle(number_of_lines);
        print_triangle(triangle, number_of_lines);
        free_triangle(triangle, number_of_lines);
}

uint8_t prime(size_t n){
  for (size_t i=2; i*i<=n; i++){
    if (n%i == 0) return 0;
  }
  return 1;
}


size_t find_k(size_t n, size_t p){
  size_t power = p;
  size_t k = 0;
  while (power<=n){
    k+= n/power;
    power*=p;
  }
  return k;
}

void find_power_k(){
  size_t n, p;
  printf("Citeste n: ");
  scanf("%zu", &n);
  printf("Citeste k:");
  scanf("%zu", &p);
  if (!prime(p)){
    printf("P nu este numar prim!!!\n");
    return;
  }
  printf("Puterea lui p in descompunerea lui n! este %zu\n", find_k(n, p));
}

int main(){
  size_t exit = 0;
  while(!exit){
    menu();
    int32_t user_input;
    printf("Input: ");
    scanf("%d", &user_input);
    switch (user_input) {
      case 2: {
            find_power_k();
            break;
          }
      case 1:{
            generate_the_pascal_triangle();
            break;
        }
      case 0:
        {exit = 1;
        break;}

      
    }
  }
  return 0;
}
