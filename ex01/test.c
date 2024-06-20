#include <stdbool.h>
#include <stdio.h>

#define BUF_SIZE 32

bool isInteger(char* str) {
  for (int i = 0; str[i] != '\0' && i < BUF_SIZE; i++) {
    if (str[1] == '\0' && !('0' <= str[0] && str[0] <= '9'))
      return false;
    else if (i == 0) {
      if (!(str[i] == '-' || str[i] == '+' || ('0' <= str[i] && str[i] <= '9')))
        return false;
    } else if (i > 0) {
      if (!('0' <= str[i] && str[i] <= '9')) return false;
    }
  }

  return true;
}

int main() {
  char buf[BUF_SIZE + 1];
  scanf("%s", buf);
  if (isInteger(buf))
    puts("Integer");
  else
    puts("Not integer");
}