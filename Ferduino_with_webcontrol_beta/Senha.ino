#ifdef USE_TFT
//coloca a senha em uma string
void updateStr(int val)
{
  stCurrent[stCurrentLen]=val;
  stCurrent[stCurrentLen+1]='\0';
  stCurrentLen++;
  myGLCD.setFont(BigFont);
  setFont(LARGE, 0, 255, 0, 0, 0, 0);
  myGLCD.print("*", 110 +((stCurrentLen -1)*16), 210);
}
#endif
