#include "dod.hpp"
#include <assert.h>

namespace dod {

    const char* data_path = "..\\..\\..\\data\\data.bin"; 

    void
    data_buffer_create_and_init(
        buffer& buf) {

        // open the file
        const HANDLE data_file_hnd = CreateFile(
            data_path,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
        assert(data_file_hnd != INVALID_HANDLE_VALUE);
  
        // get the file size
        LARGE_INTEGER size;
        GetFileSizeEx(data_file_hnd, &size);
        assert(size.LowPart != 0);

        // allocate memory
        buf.length = size.LowPart;
        buf.data   = (char*)VirtualAlloc(
            NULL, 
            buf.length,
            MEM_RESERVE | MEM_COMMIT,
            PAGE_READWRITE
        );
        assert(buf.data != NULL);
     
        // read the file
        DWORD bytes_read = 0;
        ReadFile(
            data_file_hnd,
            buf.data,
            buf.length,
            &bytes_read,
            NULL
        );
        assert(bytes_read == buf.length);
    
        // close the file
        CloseHandle(data_file_hnd);
    }
    
    void
    data_buffer_destroy(
        buffer& buf) {

        VirtualFree(
            (void*)buf.data,
            buf.length,
            MEM_RELEASE
        );
    }
};
