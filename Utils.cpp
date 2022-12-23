#define TO_UPPER(s) (((s) >= 'a' && (s) <= 'z') ? ((s) - 'a') + 'A' : (s))

namespace sdds {
    int strLen(const char *str)
    {
        int size = 0;
        while (*(str + size) != '\0')
            ++size;
        return size;
    }
    int compareCaseInsensitiveString(const char *str1, const char *str2)
    {
        int result = 0;
        if (strLen(str1) != strLen(str2))
            result = -1;
        else
            for (int i = 0; *(str1 + i) != '\0'; ++i) {
                if (TO_UPPER(*(str1 + i)) != TO_UPPER(*(str2 + i))) {
                    result = -1;
                    break;
                }
            }
        return result;
    }

}