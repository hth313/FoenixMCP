(define memories
  '((memory flash (address (#x10000 . #x1ffff))
            (section farcode cfar chuge switch data_init_table ifar))
    (memory LoRAM (address (#x4000 . #x8fff))
            (section stack data zdata data heap))
    (memory LoCODE (address (#x9000 . #xefff))
            (section code cdata))
    (memory NearRAM (address (#x20000 . #x27fff))
            (section znear near))
    (memory NearFlash (address (#x28000 . #x2ffff))
            (section cnear))
    (memory FarRAM1 (address (#x30000 . #x3ffff))
            (section far huge))
    (memory FarRAM2 (address (#x40000 . #x4ffff))
            (section zfar zhuge ))
    (memory DirectPage (address (#xf000 . #xf0ff))
            (section (registers ztiny)))
    (memory Vector (address (#xfff0 . #xffff))
            (section (reset #xfffc)))
    (block stack (size #x1000))
    (block heap (size #x1000))
    (base-address _DirectPageStart DirectPage 0)
    (base-address _NearBaseAddress NearRAM    0)
    ))