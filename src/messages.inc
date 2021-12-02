section .rodata
keyword:
  db "Enter a keyword to search for a value", 0xa, "[can contain spaces]: ", 0
empty_string:
  db "ERROR: Empty string is not allowed.", 0xa, 0x0
buffer_overflow:
  db "ERROR: No more than 255 characters allowed.", 0xa, 0x0
not_found:
  db "ERROR: Keyword not found in Dictionary!", 0xa, 0x0
