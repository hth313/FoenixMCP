(define memories
  '((memory flash (address (#x10000 . #x3ffff)) (type rom))
    (memory LoRAM (address (#x4000 . #x8fff))
            (section stack data zdata data heap))
    (memory LoCODE (address (#x9000 . #xefff))
            (section code cdata jumptable))
    (memory NearRAM (address (#x40000 . #x47fff))
            (section znear near))
    (memory NearFlash (address (#x48000 . #x4ffff))
            (section cnear))
    (memory FarRAM1 (address (#x50000 . #x5ffff))
            (section far huge))
    (memory FarRAM2 (address (#x60000 . #x6ffff))
            (section zfar zhuge ))
    (memory DirectPage (address (#xf000 . #xf0ff))
            (section (registers ztiny)))
    (memory Vector (address (#xffe0 . #xffff))
            (section (reset #xfffc)))
    (block stack (size #x1000))
    (block heap (size #x1000))
    (base-address _DirectPageStart DirectPage 0)
    (base-address _NearBaseAddress NearRAM    0)
    ))
