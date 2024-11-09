#ifndef TEXT_HEADER 
#define TEXT_HEADER 




void DrawText(uint8_t column, uint8_t row, char* text) BANKED;
uint8_t GetCharacterVRamTile(char character) BANKED;

#endif