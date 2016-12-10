
#ifndef OS_STREAM_H_
#define OS_STREAM_H_


#include <os/common.h>
#include <os/cstring.h>

namespace os {
namespace io {

// class writer_contract {
//     bool write(const byte_t) : stream, writer_base
//     writer_contract() : writer_base
// };

// class writer_base_contract {
//     size_t write(const byte_t*, size_t) : stream
//     writer_base_contract() : stream
// };

// _writer : writer_contract
template <class _writer>
class writer_base : public _writer {
public:

    size_t write(const byte_t* buf, size_t sz) {
        if(!buf || !sz) {
            return 0;
        }

        for(uint16_t i=0; i<sz; ++i) {
            if(!this->_writer::write(buf[i])) {
                return i;
            }
        }

        return sz;
    }
};

// template <class _writer>
// class stream_contract {
//     bool write(const byte_t, _writer&);
//     stream(_writer& writer);
// };

template <class _writer, template <typename> class _base = writer_base>
class stream {
public:
    bool write(const byte_t b) {
        return writer._writer::write(b);
    }

    size_t write(const byte_t* buf, size_t sz) {
        return writer.write(buf, sz);
    }

    size_t write(os::cstring_t str) {
        if(!str) {
            return 0;
        }

        size_t n = 0;
        while(*str) {
            if(!write(*str++)) {
                return n;
            }
            ++n;
        }
        return n;
    }

    size_t write(os::flash_cstring_t str) {
        if(!str) {
            return 0;
        }

        PGM_P s = reinterpret_cast<PGM_P>(str);
        size_t n = 0;
        byte_t b = pgm_read_byte(s++);
        while (b) {
            if(!writer._writer::write(b)) {
                return n;
            }
            ++n;
            b = pgm_read_byte(s++);
        }
        return n;
    }

private:
    _base<_writer> writer;
};


}
}


#endif // OS_STREAM_H_
