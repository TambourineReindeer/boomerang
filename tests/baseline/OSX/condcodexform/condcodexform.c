// address: 0x1b70
int main(int argc, char *argv[], char *envp[]) {
    unsigned int CR0; 		// r64
    unsigned int CR1; 		// r65
    unsigned int CR2; 		// r66
    unsigned int CR3; 		// r67
    unsigned int CR4; 		// r68
    unsigned int CR5; 		// r69
    unsigned int CR6; 		// r70
    __size32 CR7; 		// r71
    __size32 g0; 		// r0
    __size32 g9; 		// r9
    __size32 local0; 		// m[g1 - 40]
    __size32 local1; 		// m[g1 - 36]
    __size32 local2; 		// m[g1 - 32]
    __size32 local3; 		// m[g1 - 28]
    __size32 local4; 		// m[g1 - 24]
    __size32 local5; 		// m[g1 - 48]

    local0 = 1;
    if (argc <= 1) {
        local0 = 0;
    }
    if (local0 == 0) {
        g9 = *(/* machine specific */ (int) LR + 1200);
        local1 = g9;
    } else {
        g9 = *(/* machine specific */ (int) LR + 1204);
        local1 = g9;
    }
    if (local0 == 0) {
        g9 = *(/* machine specific */ (int) LR + 1192);
        local2 = g9;
    } else {
        g9 = *(/* machine specific */ (int) LR + 1196);
        local2 = g9;
    }
    if (local0 == 0) {
        g9 = *(/* machine specific */ (int) LR + 1184);
        local3 = g9;
    } else {
        g9 = *(/* machine specific */ (int) LR + 1188);
        local3 = g9;
    }
    if (local0 == 0) {
        g9 = *(/* machine specific */ (int) LR + 1176);
        local4 = g9;
    } else {
        g9 = *(/* machine specific */ (int) LR + 1180);
        local4 = g9;
    }
    if (argc <= 1) {
        local5 = 0;
        g0 = *(/* machine specific */ (int) LR + 1200);
        if (local1 == g0) {
            g0 = *(/* machine specific */ (int) LR + 1192);
            if (local2 == g0) {
                g0 = *(/* machine specific */ (int) LR + 1184);
                if (local3 == g0) {
                    g0 = *(/* machine specific */ (int) LR + 1176);
                    if (local4 == g0) {
                        local5 = 1;
                    }
                }
            }
        }
    } else {
        local5 = 0;
        g0 = *(/* machine specific */ (int) LR + 1204);
        if (local1 == g0) {
            g0 = *(/* machine specific */ (int) LR + 1196);
            if (local2 == g0) {
                g0 = *(/* machine specific */ (int) LR + 1188);
                if (local3 == g0) {
                    g0 = *(/* machine specific */ (int) LR + 1180);
                    if (local4 == g0) {
                        local5 = 1;
                    }
                }
            }
        }
    }
    if (local5 == 0) {
        printf(/* machine specific */ (int) LR + 1132);
    } else {
        printf(/* machine specific */ (int) LR + 1124);
    }
    return ROTL((CR0 * 0x10000000 + CR1 * 0x1000000 + CR2 * 0x100000 + CR3 * 0x10000 + CR4 * 0x1000 + CR5 * 256 + CR6 * 16 + CR7)) & 0x1;
}

