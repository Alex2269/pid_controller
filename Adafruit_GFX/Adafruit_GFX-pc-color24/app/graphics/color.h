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

#define ALICEBLUE 0xF0F8FF
#define ANTIQUEWHITE 0xFAEBD7
#define AQUA 0x00FFFF
#define AQUAMARINE 0x7FFFD4
#define AZURE 0xF0FFFF
#define BEIGE 0xF5F5DC
#define BISQUE 0xFFE4C4
#define BLACK 0x000000
#define BLANCHEDALMOND 0xFFEBCD
#define BLUE 0x0000FF
#define BLUEVIOLET 0x8A2BE2
#define BROWN 0xA52A2A
#define BURLYWOOD 0xDEB887
#define CADETBLUE 0x5F9EA0
#define CHARTREUSE 0x7FFF00
#define CHOCOLATE 0xD2691E
#define CORAL 0xFF7F50
#define CORNFLOWERBLUE 0x6495ED
#define CORNSILK 0xFFF8DC
#define CRIMSON 0xDC143C
#define CYAN 0x00FFFF
#define DARKBLUE 0x00008B
#define DARKCYAN 0x008B8B
#define DARKGOLDENROD 0xB8860B
#define DARKGRAY 0xA9A9A9
#define DARKGREEN 0x006400
#define DARKKHAKI 0xBDB76B
#define DARKMAGENTA 0x8B008B
#define DARKOLIVEGREEN 0x556B2F
#define DARKORANGE 0xFF8C00
#define DARKORCHID 0x9932CC
#define DARKRED 0x8B0000
#define DARKSALMON 0xE9967A
#define DARKSEAGREEN 0x8FBC8F
#define DARKSLATEBLUE 0x483D8B
#define DARKSLATEGRAY 0x2F4F4F
#define DARKTURQUOISE 0x00CED1
#define DARKVIOLET 0x9400D3
#define DEEPPINK 0xFF1493
#define DEEPSKYBLUE 0x00BFFF
#define DIMGRAY 0x696969
#define DODGERBLUE 0x1E90FF
#define FIREBRICK 0xB22222
#define FLORALWHITE 0xFFFAF0
#define FORESTGREEN 0x228B22
#define FUCHSIA 0xFF00FF
#define GAINSBORO 0xDCDCDC
#define GHOSTWHITE 0xF8F8FF
#define GOLD 0xFFD700
#define GOLDENROD 0xDAA520
#define GRAY 0xBEBEBE
#define GRAY50 0x7F7F7F
#define GREEN 0x00FF00
#define GREENYELLOW 0xADFF2F
#define HONEYDEW 0xF0FFF0
#define HOTPINK 0xFF69B4
#define INDIANRED 0xCD5C5C
#define INDIGO 0x4B0082
#define IVORY 0xFFFFF0
#define KHAKI 0xF0E68C
#define LAVENDER 0xE6E6FA
#define LAVENDERBLUSH 0xFFF0F5
#define LAWNGREEN 0x7CFC00
#define LEMONCHIFFON 0xFFFACD
#define LIGHTBLUE 0xADD8E6
#define LIGHTCORAL 0xF08080
#define LIGHTCYAN 0xE0FFFF
#define LIGHTGOLDENROD 0xEEDD82
#define LIGHTGOLDENRODYELLOW 0xFAFAD2
#define LIGHTGRAY 0xD3D3D3
#define LIGHTGREEN 0x90EE90
#define LIGHTPINK 0xFFB6C1
#define LIGHTSALMON 0xFFA07A
#define LIGHTSEAGREEN 0x20B2AA
#define LIGHTSKYBLUE 0x87CEFA
#define LIGHTSLATEBLUE 0x8470FF
#define LIGHTSLATEGRAY 0x778899
#define LIGHTSTEELBLUE 0xB0C4DE
#define LIGHTYELLOW 0xFFFFE0
#define LIME 0x00FF00
#define LIMEGREEN 0x32CD32
#define LINEN 0xFAF0E6
#define MAGENTA 0xFF00FF
#define MAROON 0xB03060
#define MEDIUMAQUAMARINE 0x66CDAA
#define MEDIUMBLUE 0x0000CD
#define MEDIUMORCHID 0xBA55D3
#define MEDIUMPURPLE 0x9370DB
#define MEDIUMSEAGREEN 0x3CB371
#define MEDIUMSLATEBLUE 0x7B68EE
#define MEDIUMSPRINGGREEN 0x00FA9A
#define MEDIUMTURQUOISE 0x48D1CC
#define MEDIUMVIOLETRED 0xC71585
#define MIDNIGHTBLUE 0x191970
#define MINTCREAM 0xF5FFFA
#define MISTYROSE 0xFFE4E1
#define MOCCASIN 0xFFE4B5
#define NAVAJOWHITE 0xFFDEAD
#define NAVY 0x000080
#define NAVYBLUE 0x000080
#define OLDLACE 0xFDF5E6
#define OLIVE 0x808000
#define OLIVEDRAB 0x6B8E23
#define ORANGE 0xFFA500
#define ORANGERED 0xFF4500
#define ORCHID 0xDA70D6
#define PALEGOLDENROD 0xEEE8AA
#define PALEGREEN 0x98FB98
#define PALETURQUOISE 0xAFEEEE
#define PALEVIOLETRED 0xDB7093
#define PAPAYAWHIP 0xFFEFD5
#define PEACHPUFF 0xFFDAB9
#define PERU 0xCD853F
#define PINK 0xFFC0CB
#define PLUM 0xDDA0DD
#define POWDERBLUE 0xB0E0E6
#define PURPLE 0xA020F0
#define REBECCAPURPLE 0x663399
#define RED 0xFF0000
#define ROSYBROWN 0xBC8F8F
#define ROYALBLUE 0x4169E1
#define SADDLEBROWN 0x8B4513
#define SALMON 0xFA8072
#define SANDYBROWN 0xF4A460
#define SEAGREEN 0x2E8B57
#define SEASHELL 0xFFF5EE
#define SIENNA 0xA0522D
#define SILVER 0xC0C0C0
#define SKYBLUE 0x87CEEB
#define SLATEBLUE 0x6A5ACD
#define SLATEGRAY 0x708090
#define SNOW 0xFFFAFA
#define SPRINGGREEN 0x00FF7F
#define STEELBLUE 0x4682B4
#define TAN 0xD2B48C
#define TEAL 0x008080
#define THISTLE 0xD8BFD8
#define TOMATO 0xFF6347
#define TURQUOISE 0x40E0D0
#define VIOLET 0xEE82EE
#define VIOLETRED 0xD02090
#define WHEAT 0xF5DEB3
#define WHITE 0xFFFFFF
#define WHITESMOKE 0xF5F5F5
#define YELLOW 0xFFFF00
#define YELLOWGREEN 0x9ACD32

#endif // colors_H_

