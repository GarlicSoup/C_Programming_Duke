
void rotate(char matrix[][10]) {
  int len = 10;
  int temp;
  for (int i=0; i<len/2; i++) {
    for (int j=i; j<len-i-1; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[len-j-1][i];
      matrix[len-j-1][i] = matrix[len-i-1][len-j-1];
      matrix[len-i-1][len-j-1] = matrix[j][len-i-1];
      matrix[j][len-i-1] = temp;
    }
  }
}
