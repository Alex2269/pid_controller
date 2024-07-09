#ifndef colors_H_
#define colors_H_

inline uint32_t LCD_Color565_to_888(uint16_t color) {
  return (((color & 0xF800) << 8) | ((color & 0x7E0) << 5) | ((color & 0x1F) << 3));  // transform to rrrrrrxx ggggggxx bbbbbbxx
}

inline uint8_t LCD_Color565_to_R(uint16_t color) {
  return ((color & 0xF800) >> 8);  // transform to rrrrrrxx
}

inline uint8_t LCD_Color565_to_G(uint16_t color) {
  return ((color & 0x7E0) >> 3);  // transform to ggggggxx
}

inline uint8_t LCD_Color565_to_B(uint16_t color) {
  return ((color & 0x1F) << 3);  // transform to bbbbbbxx
}

inline uint16_t LCD_Color565_to_Color16(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

inline uint32_t LCD_Color888_to_Color24(uint8_t R8, uint8_t G8, uint8_t B8) {
  uint32_t color24;
  // color24 = ( R8 & 0x00ffff ) << 16 | ( G8 & 0xff00ff ) << 8 | ( B8 & 0x0000ff );
  color24 = R8 << 16 | G8 << 8 | B8;
  return color24;
}

inline uint16_t H24_RGB565(uint8_t reverse, uint32_t color24)
{
  uint8_t b = (color24 >> 16) & 0xFF;
  uint8_t g = (color24 >> 8) & 0xFF;
  uint8_t r = color24 & 0xFF;
  if (reverse) return ((b / 8) << 11) | ((g / 4) << 5) | (r / 8);
  else return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

// RGB565 conversion
// RGB565 is R(5)+G(6)+B(5)=16bit color format.
// Bit image "RRRRRGGGGGGBBBBB"
inline uint16_t rgb565_conv(uint16_t r,uint16_t g,uint16_t b)
{
  unsigned int RR,GG,BB;
  RR = (r * 31 / 255) << 11;
  GG = (g * 63 / 255) << 5;
  BB = (b * 31 / 255);
  return(RR | GG | BB);
}

#define MAROON                 0x8000
#define DARKRED                0x8800
#define BROWN                  0xA145
#define FIREBRICK              0xB104
#define CRIMSON                0xD8A7
#define RED                    0xF800
#define TOMATO                 0xFB09
#define CORAL                  0xFBEA
#define INDIANRED              0xCAEB
#define LIGHTCORAL             0xEC10
#define DARKSALMON             0xE4AF
#define SALMON                 0xF40E
#define LIGHTSALMON            0xFD0F
#define ORANGERED              0xFA20
#define DARKORANGE             0xFC60
#define ORANGE                 0xFD20
#define GOLD                   0xFEA0
#define DARKGOLDENROD          0xB421
#define GOLDENROD              0xDD24
#define PALEGOLDENROD          0xEF35
#define DARKKHAKI              0xBDAD
#define KHAKI                  0xEF31
#define OLIVE                  0x8400
#define YELLOW                 0xFFE0
#define YELLOWGREEN            0x9E66
#define DARKOLIVEGREEN         0x5346
#define OLIVEDRAB              0x6C64
#define LAWNGREEN              0x7FC0
#define CHARTREUSE             0x7FE0
#define GREENYELLOW            0xAFE6
#define DARKGREEN              0x0320
#define GREEN                  0x07E0
#define FORESTGREEN            0x2444
#define LIME                   0x07E0
#define LIMEGREEN              0x3666
#define LIGHTGREEN             0x9772
#define PALEGREEN              0x97D2
#define DARKSEAGREEN           0x8DD1
#define MEDIUMSPRINGGREEN      0x07D3
#define SPRINGGREEN            0x07EF
#define SEAGREEN               0x344B
#define MEDIUMAQUAMARINE       0x6675
#define MEDIUMSEAGREEN         0x3D8E
#define LIGHTSEAGREEN          0x2595
#define DARKSLATEGRAY          0x328A
#define TEAL                   0x0410
#define DARKCYAN               0x0451
#define AQUA                   0x07FF
#define CYAN                   0x07FF
#define LIGHTCYAN              0xDFFF
#define DARKTURQUOISE          0x0679
#define TURQUOISE              0x46F9
#define MEDIUMTURQUOISE        0x4E99
#define PALETURQUOISE          0xAF7D
#define AQUAMARINE             0x7FFA
#define POWDERBLUE             0xAEFC
#define CADETBLUE              0x64F3
#define STEELBLUE              0x4C16
#define CORNFLOWERBLUE         0x64BD
#define DEEPSKYBLUE            0x05FF
#define DODGERBLUE             0x249F
#define LIGHTBLUE              0xAEBC
#define SKYBLUE                0x867D
#define LIGHTSKYBLUE           0x867E
#define MIDNIGHTBLUE           0x18CE
#define NAVY                   0x0010
#define DARKBLUE               0x0011
#define MEDIUMBLUE             0x0019
#define BLUE                   0x001F
#define ROYALBLUE              0x435B
#define BLUEVIOLET             0x897B
#define INDIGO                 0x4810
#define DARKSLATEBLUE          0x49F1
#define SLATEBLUE              0x6AD9
#define MEDIUMSLATEBLUE        0x7B5D
#define MEDIUMPURPLE           0x939B
#define DARKMAGENTA            0x8811
#define DARKVIOLET             0x901A
#define DARKORCHID             0x9999
#define MEDIUMORCHID           0xBABA
#define PURPLE                 0x8010
#define THISTLE                0xD5FA
#define PLUM                   0xDD1B
#define VIOLET                 0xEC1D
#define MAGENTA                0xF81F
#define ORCHID                 0xDB9A
#define MEDIUMVIOLETRED        0xC0B0
#define PALEVIOLETRED          0xDB92
#define DEEPPINK               0xF8B2
#define HOTPINK                0xFB56
#define LIGHTPINK              0xFDB7
#define PINK                   0xFDF9
#define ANTIQUEWHITE           0xF75A
#define BEIGE                  0xF7BB
#define BISQUE                 0xFF18
#define BLANCHEDALMOND         0xFF59
#define WHEAT                  0xF6F6
#define CORNSILK               0xFFBB
#define LEMONCHIFFON           0xFFD9
#define LIGHTGOLDENRODYELLOW   0xF7DA
#define LIGHTYELLOW            0xFFFB
#define SADDLEBROWN            0x8A22
#define SIENNA                 0x9A85
#define CHOCOLATE              0xD344
#define PERU                   0xCC28
#define SANDYBROWN             0xF52C
#define BURLYWOOD              0xDDB0
#define TAN                    0xD591
#define ROSYBROWN              0xBC71
#define MOCCASIN               0xFF16
#define NAVAJOWHITE            0xFEF5
#define PEACHPUFF              0xFED6
#define MISTYROSE              0xFF1B
#define LAVENDERBLUSH          0xFF7E
#define LINEN                  0xF77C
#define OLDLACE                0xFFBC
#define PAPAYAWHIP             0xFF7A
#define SEASHELL               0xFFBD
#define MINTCREAM              0xF7FE
#define SLATEGRAY              0x7412
#define LIGHTSLATEGRAY         0x7453
#define LIGHTSTEELBLUE         0xAE1B
#define LAVENDER               0xE73E
#define FLORALWHITE            0xFFDD
#define ALICEBLUE              0xEFBF
#define GHOSTWHITE             0xF7BF
#define HONEYDEW               0xEFFD
#define IVORY                  0xFFFD
#define AZURE                  0xEFFF
#define SNOW                   0xFFDE
#define BLACK                  0x0000
#define DIMGRAY                0x6B4D
#define GRAY                   0x8410
#define DARKGRAY               0xAD55
#define SILVER                 0xBDF7
#define LIGHTGRAY              0xD69A
#define GAINSBORO              0xDEDB
#define WHITESMOKE             0xF7BE
#define WHITE                  0xFFFF

#endif // colors_H_

