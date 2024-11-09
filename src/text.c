#pragma bank 255

#include <gb/gb.h>
#include <stdint.h>


uint8_t GetCharacterVRamTile(char character) BANKED{

    uint8_t vramTile=0;


    // Char's can be interpreted as integers
    // We don't need to map every alpha-numeric character
    // We can use basic math to simplify A-Z and 0-9
    if(character>='a'&&character<='z')vramTile = (character-'a')+1;
    else if(character>='A'&&character<='Z')vramTile = (character-'A')+1;
    else if(character>='0'&&character<='9')vramTile = (character-'0')+27;
    else if(character=='.')vramTile = 37;
    else if(character==',')vramTile = 38;
    else if(character=='!')vramTile = 39;
    else if(character=='?')vramTile = 40;
    else if(character=='~')vramTile = 41;

    return vramTile;

}

void DrawText(uint8_t column, uint8_t row, char* text) BANKED{

    // Get the address of the first tile in the row
    uint8_t* vramAddress = get_bkg_xy_addr(column,row);

    uint16_t index=0;

    while(text[index]!='\0'){

        char character = text[index];

        // Draw our character at the address
        // THEN, increment the address
        uint8_t vramTile = GetCharacterVRamTile(character);

        set_vram_byte(vramAddress++,vramTile);

        index++;

    }
}