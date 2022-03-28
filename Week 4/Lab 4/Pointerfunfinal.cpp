#include <iostream>
#include <cstring>



int main() {
    const char*   c[]   = { "ENTER", "NEW", "POINT", "FIRST" };
    const char**  cp[]  = { c+3, c+2, c+1, c };
    const char*** cpp   = cp;
    char          s[13] = "";

    strcat(s, *(*(++cpp)));             // *(++cpp) = *(cp + 1)
                                        // *(cp + 1) = c + 2
                                        // c + 2 = "POINT"
    strcat(s, *(--(*(++cpp))) + 3);     // *(++cpp) = *(cp + 2) = c + 1
                                        // --(c + 1) = c
                                        // *(c + 1) = "ENTER"
                                        // "ENTER" + 3 = "ER"
    strcat(s, " ");                     // add space
    strcat(s, *(*(cpp - 2)) + 3);        // *(cpp - 2) = *(cp)
                                        // *(cp) = c + 3
                                        // *(c + 3) = "FIRST"
                                        // "FIRST" + 3 = "ST"
    strcat(s, cpp[-1][-1] + 1);         // *(cp + 2 - 1) 
                                        // *(cpp - 1)[-1] + 1 
                                        // == *(*(cpp - 1) - 1) + 1
                                        
                                        // "NEW" + 1 = "EW"

std::cout << s << '\n';
    return 0;
}


