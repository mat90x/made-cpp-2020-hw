#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    return number & 0x1ull << index;
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0x0ull;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x1ull << 63;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7ffull << 52;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xfffull << 52;
}

bool checkForNormal (uint64_t number) {
    uint64_t exp = number & 0x7ffull << 52;
    return 0x1ull << 52 <= exp && exp <= 0x7feull << 52 && number & 0xfffffffffffffull;
}

bool checkForPlusNormal (uint64_t number) {
    return !getBit(number, 63) && checkForNormal(number);
}

bool checkForMinusNormal (uint64_t number) {
    return getBit(number, 63) && checkForNormal(number);
}

bool checkForDenormal (uint64_t number) {
    uint64_t exp = number & 0x7ffull << 52;
    return !exp && number & 0xfffffffffffffull;
}

bool checkForPlusDenormal (uint64_t number) {
    return !getBit(number, 63) && checkForDenormal(number);
}

bool checkForMinusDenormal (uint64_t number) {
    return getBit(number, 63) && checkForDenormal(number);
}

bool checkForSignalingNan (uint64_t number) {
    uint64_t onesMask = 0x7ffull << 52;
    return !getBit(number, 51) && ((number & onesMask) == onesMask) && number & 0x7ffffffffffffull;
}

bool checkForQuietNan (uint64_t number) {
    uint64_t onesMask = 0x7ffull << 52;
    return getBit(number, 51) && ((number & onesMask) == onesMask);
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
