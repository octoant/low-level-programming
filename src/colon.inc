%define invalid_arg1 "The first colon arg must be a string"
%define invalid_arg2 "The second colon arg must be a valid label"
%define head 0

%macro colon 2
  %ifstr %1
    %2: dq head
    db %1, 0
  %else
    %error invalid_arg1
  %endif
  %ifid %2
    %define head %2
  %else
    %error invalid_arg2
  %endif
%endmacro
