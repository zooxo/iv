# IVEE - a Powerful Programable RPN Calculator based on FORTH
  ____________________

##  +++ the source code is coming soon - please be patient +++
  ____________________

  Welcome to Ivee (IV) - A Powerful Programable RPN Calculator based on FORTH   
  Version 1.0, (c) 2020 by deetee/zooxo   
  This software is covered by the 3-clause BSD license.   
  ____________________


  ____________________

   PREAMBLE
  ____________________

  Ivee is a powerful programable RPN calculator based on the programming
  language FORTH. This innovative and powerful machine benefits of a brilliant
  symbiosis, as both - the RPN calculator and FORTH - are stack based systems.
  The name Ivee or IV stands for the roman number 4, which was also a basis for
  naming Forth (4th generation of programming languages).

  Ivee complements a viable set of Forth words (26 commands) with a set of
  system oriented commands and additional built-in Forth words. In addition
  the user can define/program new words based on existing words and commands.

  The hardware is simple:
    - Arduino Pro Micro
    - OLED display (128x64 pixel) with SSD1306- or SSD1309-controller
    - 16 keys (push buttons)
    optional: - LIPO battery
              - LIPO battery charger (TP4056)
              - ON/OFF-switch

  Allthough Ivee is operated by 16 keys only it offers a wide range of functions
  and possibilities:
  - 120 intrinsic functions based on FORTH
  - Programming: Handle up to 40 user definable programs
                 (Edit, New, Rename, Move, Delete, Send, Load)
  - Dictionary of all commands, words and programs
  - Fast user definable menu (longpressed F-key)
  - Calculations with complex numbers for nearly every function
  - Calculus (f(x), plot, solve, integrate)
  - Basic math operations in number systems with selectable BASE
  - Business calculator mode (accuracy of 18 digits)
  - Save up to 10 numbers/constants permanently
  - Statistics and line best fit
  - Many unit conversions
  - Clock and Torch function
  - Basic system functions (Battery voltage, Brightness, Screensaver)

  Have fun!
  deetee

  ____________________

   KEYBOARD, SHORTCUTS
  ____________________

    F(G)[OFF]{MENU}  7(S+)[SCLR]    8(PRG)[BASE]    9(/)[MOD]
    E(SWAP)[ROT]     4(DICT)[USR]   5(FX)[FPLOT]    6(*)[LIT]
    N(OVER)[PICK]    1(RCL)[STO]    2(SOLVE)[FINT]  3(-)[LIT-]
    X(CLR)[TOFF]     0(CPLX)[BATT]  .(R<>P)[CLK]    #(+)[LIT+]

    PRG Shortcuts:                  BASE/HEX Shortcuts:
              5 OUT  6 UP             4 E  5 F
      1 NEW   2 IN   3 DOWN           1 B  2 C    3 D
      0 REN  . DEL  D EDIT            0 A  . A~F

    MENU/DICT/REN Navigation:       SUM/STAT/L.R. Storage Registers:
             Q1  Q2  Q3  Q4           7 SN  8 SX   9 SY
      UP     E   4   5   6                  5 SXX  6 SXY
      DOWN   N   1   2   3
             PREV0   .NEXT

  ____________________

   DISPLAY, INDICATORS
  ____________________

    >        ... Empty stack, ready to calculate
    >        ... Indicates selected program in program selection mode
    <        ... Indicates selected program step in program editing mode
    a~z      ... Stack level
    _        ... Indicates number input
    i, angle ... Imaginary part, imaginary angle
    B        ... BASE mode indicator
    n BASE   ... Numeric base of BASE mode
    !        ... Indicates float of data stack (data loss in lowest stack level)
    ^, v     ... F-key, G-key

  ____________________

   LIMITS
  ____________________

  As a microprocessor is primarily not made to do such complex things like
  performing a powerful calculator there are some limits in performance and
  resources.
  Most obviously is the limited precision of the intrinsic float format (IEEE
  754, 32 bit). As four bytes only are used to represent a float respective
  double number the decimal digits of precision is limited to 6...7. For
  example calculating sqrt(-1) yields in a display of "7.5E-8 + i" (instead of
  "0 + i").
  In addition the resources of a microcontroller are limited like the FLASH
  memory (holds the executable program code), the RAM memory (holds variables
  and data while running) and the EEPROM (holds permanent data like settings or
  user programs).
  However Ivee tries to offer a maximum of features, comfort and performance
  with a minimum of required resources.

  LIMITS:   
    26   ... Maximal data stack size (a...z)
    7    ... Maximum number of displayed significant digits of a number
    36   ... Maximum number of decimal exponent digits (1E-37 < X < 1E37)
    12   ... Maximal size of text display (see EMIT, CTX)
    10   ... Maximal amount of (complex) numbers saved permanently (0...9)
    3    ... Maximal number of characters for naming an user program
    40   ... Maximal number of user programs
    128  ... Maximal size of an user program (steps)
    900  ... Maximal size (steps) of all user programs
    64   ... Maximal size of address stack ("deep of nesting")
    1E-4 ... X-range of solver (Newton) to determine slope of function
    10   ... Calculation "stripes" for integrating (Simpson)
    32   ... Maximal definable command slots of user menu

  ____________________

   BROWSING MENUS
  ____________________

    To navigate through the menu of some functions (MENU, DICT, USR, renamePRG)
    all selectable items are divided into four sections. Every section has its
    own up and down key (section I: E/N, section II: 4/1, section III: 5/2 and
    section IV: 6/3).
    To move to the previous or next entry (regardless which section is selected)
    the keys "0" or "." can be used. To select one of the four presented items
    use the appropriate function key (F/7/8/9) or escape the menu with "X".

  ____________________

   PROGRAMMING
  ____________________

    Ivee is able to deal with up to 40 user programs with a total number of
    900 steps/commands. To deal with programs enter the program selector mode
    with PRG.
    While in the program selection mode on the left side of the display the
    available programs are numbered and listed. On the right side of the display
    the number of programs, the memory used and the memory available are shown.
    To navigate between programs use the cursor keys E (up) and N (down).
    Edit a selected program with # or press 1 to enter a new program.
    To delete a program press "." - to rename it use the key 0.
    You can move a program with 6 up or with 3 down. Note that the top program
    has special calculus features (f(x), plot, solve, integrate).
    To send a program (does not include the program name) via USB to another
    computer press "5". Note that corresponding ascii characters will be sent
    (see chapter DICTIONARY, second column). In a similar way programs can be
    send from another computer to Ivee (press key 2) and will be stored as new
    program.
    With the 3 powerful commands @, ! and EXE (see chapter DICTIONARY) it is
    even possible to manipulate the program memory and execute code.
    A program is structured into the three parts NAME, COMMANDS and EOP-marker.
    Please note that the length of the program name is restricted to 3
    characters and the maximum number of program steps is restricted to 128.

  ____________________

   BASE, BUSINESS MODE
  ____________________

    To calculate with integer values with other numeric base enter the base and
    select the BASE command (ie 16 BASE to calculate with hexadecimal numbers).
    To return to the scientific mode press BASE again. When changing the mode
    the whole stack will be converted (as far as appropriate) to the new base.
    Numbers will be displayed in groups of four digits in two lines with a
    B-indicator (BASE) on the left side and the base itself on the right side of
    the first line. Pressing "E" enters four zeros.
    Note that only basic operations (/*-+) and some stack operations are
    supported. To enter digits bigger than 9 (ie F) press "." followed by a key
    (ie 5 to enter F).
    The BASE state will be stored permanently.
    Entering the BASE mode with 10 activates the business mode to deal with big
    numbers and high accuracy, like trillions of dollars with cent accuracy.
    Numbers are grouped into triples and two digits after the decimal dot
    (cents) are supported.

  ____________________

   CALCULUS
  ____________________

    Ivee is able to analyze the first user defined program. Note that you can
    move the desired user program to the first position using the keys 6 or 3
    in program mode (PRG).
    To calculate the value of a function use F(X).
    To find the root of a function enter a start value (X) and press FSOLVE.
    Enter the x-range (from Y to X) before plotting a function (FPLOT) or
    calculating an integral (FINT).

  ____________________

   COMMANDS
  ____________________

  MEMORY
       functions         mem[]       EEPROM
    |<--intrinsic-->|<--builtin-->|<--user-->|
     0               76            120        160
              MAXCMDI^      MAXCMDB^   MAXCMDU^


  OVERVIEW
    Intrinsic
      Forth  DUP DROP NEGATE / * - + MOD DICT SWAP ROT PICK
             < = <> > KEY EMIT BASE BEGIN UNTIL IF ELSE THEN @ !
      System 0~9 . E STO RCL CLR USR NAND INTEGER PI INV SIN EXP LN
             COMPLEX REC<>POL F(X) FPLOT FSOLVE FINTEGRATE
             PRG T+ PSE EXE BREAK CLRTEXT ISREAL
             SUM+ SUM- SUMCLR COMB PERM STAT LR
             BATT LIT LIT+ LIT- CLOCK OFF TOFF
    Builtin
      Forth  OVER HEX AND NOT OR ABS
      Other  $ SQRT POWER POWER10 LOG LN! PV ND QE HMS>H H>HMS CLOCK
             COS TAN ASIN ACOS ATAN SINH COSH TANH ASINH ACOSH ATANH
             DEG>RAD RAD>DEG C>F F>C KM>MI MI>KM M>FT FT>M CM>IN IN>CM

```
  DICTIONARY (in order of "appearence")
    000   0     ... Numbers
    001 ! 1
    002 " 2
    003 # 3
    004 $ 4
    005 % 5
    006 & 6
    007 ' 7
    008 ( 8
    009 ) 9
    010 * .     ... Dot key
    011 + DUP   ... Duplicate, end number input
    012 , DROP  ... Drop X, clear entry
    013 - N     ... NEG, change sign (negate X)
    014 . E     ... Enter 10th exponent (actually Y*10^X)
    015 / F     ... Function key (Shift)
    016 0 CPLX  ... Enter complex number and vice versa (see R<>P)
    017 1 RCL   ... Recall memory (number = X) from permanent memory. Note that
                    the memories 5...9 are used as statistic registers.
    018 2 FSOLV ... Find the root of the first user defined program/function
                    (PRG) using X as start value
    019 3 -     ... Substract (X = Y-X)
    020 4 DICT  ... Catalog all functions (see section BROWSING MENUS)
    021 5 F(X)  ... Calculate first user defined program/function (PRG)
    022 6 *     ... Multiply (X = Y*X)
    023 7 S+    ... Add values of X- and Y-register to sums (see STAT/LR)
    024 8 PRG   ... Enter program mode (see section PROGRAMMING)
    025 9 /     ... Divide (X = Y/X)
    026 : R<>P  ... Toggle rectangular or polar mode (see CPLX)
    027 ; +     ... Addition (X = Y+X)
    028 < CLR   ... Clear stack and alpha register
    029 = OVER  ... Push/copy Y to stack (YX -> YXY)
    030 > SWAP  ... Swap last two stack contents (XY -> XY)
    031 ? G     ... Second function key (Shift-Shift)
    032 @ BATT  ... Show battery voltage (push to stack)
    033 A STO   ... Store Y memory (number = X). Note that the memories 5...9
                    are used as statistic registers (Sxx, Sxy, n, Sx, Sy).
    034 B FINT  ... Integrate the first user defined program (PRG) using
                    the x-range from Y to X
    035 C B-    ... Lower the brightness of the display (5 levels). Note that
                    the display has to be rebooted (needs two seconds).
    036 D USR   ... Set function key of (custom) user MENU
    037 E FPLOT ... Plot the first user defined program (PRG) using the the
                    x-range from Y to X. Escape with key "X".
    038 F LIT   ... Illuminate the whole display
    039 G SCLR  ... Clear all sum register. Note that statistic functions are
                    using the permanent memories 5...9.
    040 H BASE  ... Set number base for integer calculations (i.e. 2, 8, 16).
                    Note that setting the base to 10 enters the business
                    calculator mode (see chapter BASE, BUSINESS MODE).
    041 I MOD   ... Modulo, division remainder (X = Y%X)
    042 J CLOCK ... Simple clock. To set the time use hh.mmss.
    043 K LIT+  ... Rise the brightness of the display (5 levels). Note that
                    the display has to be rebooted (needs two seconds).
    044 L TOFF  ... Set the screen off time (x 10 s) (>=3)
    045 M PICK  ... Copy n-th number of stack to stack
    046 N ROT   ... Rotate 3 numbers of stack (ZYX -> YXZ)
    047 O DARK  ... Enter screen off manually (triple press F)
    048 P <     ... Condition less than (returns true, if Y<X)
    049 Q =     ... Condition equal (returns true, if Y=X)
    050 R <>    ... Condition not equal (returns true, if Y<>X)
    051 S GT    ... Condition greater than (returns true, if Y>X)
    052 T NAND  ... Logical NAND (used for other logical functions)
    053 U T+    ... Adds duration in ms to stack (since last call)
    054 V PSE   ... Pause program execution for X*250 ms and print screen
    055 W INT   ... Calculate integer value of X
    056 X @     ... Fetch the value from address (X) (see also ! and EXE)
    057 Y !     ... Store Y at X-address (see also @ and EXE)
    058 Z BEGIN ... Begin a BEGIN-UNTIL-Loop
    059 [ UNTIL ... Continue executing a BEGIN-UNTIL-Loop until X is true
    060 \ EXE   ... Execute code at X-address (see also @ and !)
    061 ] IF    ... Execute the following code if true
    062 ^ ELSE  ... Execute the following code if IF failed
    063 _ THEN  ... Terminate an IF(-ELSE) condition
    064 ` BREAK ... Pause code execution for input (key "X" resumes)
    065 a KEY   ... Wait for keypress and push the keycode to stack
    066 b CTX   ... Clear text area (written with EMIT)
    067 c EMIT  ... Emit ascii character of X
    068 d RE?   ... Return true, if X is a real value
    069 e nCr   ... Calculate the combination (of yCx)
    070 f nPr   ... Calculate the permutation (of yPx)
    071 g PI    ... Push the value of PI to stack
    072 h INV   ... Push the reciprocal value of X to stack
    073 i SIN   ... Push the sine of X to stack
    074 j EXP   ... Push the exponential value of X to stack
    075 k LN    ... Push the natural logarithm of X to stack
    076 l $     ... Activate the business calculator mode (10 BASE)
    077 m HEX   ... Activate HEX mode (16 BASE)
    078 n AND   ... Logical AND
    079 o NOT   ... Logical NOT
    080 p OR    ... Logical OR
    081 q OVER  ... Push/copy Y to stack (YX -> YXY)
    082 r ABS   ... Push the absolute value of X to stack
    083 s SQRT  ... Push the quare root of X to stack

    084 t COS   ... Push the cosine of X to stack
    085 u TAN   ... Push the tangent of X to stack
    086 v POW   ... Push Y raised to the power of X to stack (X = Y^X)
    087 w 10^   ... Push 10 raised to the power of X to stack (X = 10^X)
    088 x LOG   ... Push the 10 based logarithm of X to stack
    089 y ASIN  ... Push the arcus (inverse) sinus of X to stack
    090 z ACOS  ... Push the arcus (inverse) cosine of X to stack
    091 { ATAN  ... Push the arcus (inverse) tangent of X to stack
    092 | SINH  ... Push the hyperbolic sine of X to stack
    093 } COSH  ... Push the hyperbolic cosine of X to stack
    094 ~ TANH  ... Push the hyperbolic tangent of X to stack
    095 ? ASINH ... Push the area (inverse) hyperbolic sine of X to stack
    096 ? ACOSH ... Push the area (inverse) hyperbolic cosine of X to stack
    097 ? ATANH ... Push the area (inverse) hyperbolic tangent of X to stack
    098 ? LN!   ... Push the natural logarithm of gamma of X to stack
    099 ? >h    ... Convert hh.mmss to h (HMS->H)
    100 ? h>    ... Convert h to hh.mmss (H->HMS)
    101 ? PV    ... Present value of given interest rate and periods
    102 ? ND    ... PDF (X) and CDF (Y) of standard normal distribution
    103 ? QE    ... Quadratic equation xx+Yx+X=0 X|Y=-Y/2+-sqrt(Y*Y/4-X)
    104 ? CLOCK ... Simple clock (set with hh.mmss)
    105 ? SCLR  ... Clear statistic registers (permanent memories 5...9)
    106 ? S+    ... Add values of X- and Y-register to sums (see STAT/LR)
    107 ? S-    ... Substract values of X- and Y-register to sums (see STAT/LR)
    108 ? STAT  ... Mean value (X) and standard deviation (Y). Note that the
                    permanent memories 5...9 (see RCL/STO) are used as statistic
                    registers (Sxx, Sxy, n, Sx, Sy).
    109 ? LR    ... Line best fit (y = X * x + Y)
    110 ? %     ... Percent (X/Y*100%)
    111 ? %CHG  ... Percent change (X-Y)/Y*100%
    112 ? FRAC  ... Fractional part
    113 ? ><d   ... Convert degrees to radians (and vice versa)
    114 ? ><C   ... Convert Celsius to Fahrenheit (and vice versa)
    115 ? ><km  ... Convert kilometer to miles (and vice versa)
    116 ? ><m   ... Convert meter to feet (and vice versa)
    117 ? ><cm  ... Convert centimeter to inches (and vice versa)
    118 ? ><kg  ... Convert kilogram to lbs (and vice versa)
    119 ? ><l   ... Convert liter to gallons (and vice versa)
```
  ____________________

   EEPROM
  ____________________

    ADDRESS       BYTES PURPOSE
      0 ...    0    1   Brightness
      1 ...    1    1   Screen off time (*250 ms)
      2 ...    2    1   Number base (BASE)
      3 ...   82   80   Memory area for RCL/STO (real and imaginary numbers)
     83 ...   90    8   Memory area for RCL/STO (integer number in BASE mode)
     91 ...  122   32   Memory area for user selectable MENU
    123 ... 1023  901   User program memory area

  ____________________

   MEMORY, STACKS
  ____________________

                                 | sizeof(mem)
           _ _ _ _ _ _ _ _ _ _ _ v
    mem[] |_|_|_|_|_ _ _ _ _|_|_|_|
            |<--builtinprograms-->|
            |         ^           |                    | sizeof(mem) +
           0|1        mp          |                    | sou=sizeofusr()
                      v           |_ _ _ _ _ _ _ _ _ _ v _ _ _ _ _ _ _ _
                         EEPROM[] |_|_|_|_ _ _ _ _|_|_|_|_|_|_|_|_|_|_|_|
                                  |<---user-programs--->|<-- @ ! EXE -->|
                                  |^EEUSTART                     EEUEND^|
                                  |<------- sou ------->|               |
                                  |<------------ 901 bytes ------------>|


           DATASTACK                 ADDRESSSTACK            CONDITIONAL
      (2 x double, int64)                (int)                 POINTER
    |      |      |       |             |     |
    |______|______|_______|             |_____|               <cp (byte)
    |______|______|_______|<dp (byte)   |_____|
    |______|______|_______|             |_____|<ap (int)
    |__re__|__im__|_int64_|             |_____|
             ds[]                         as[]

  ____________________

   CIRCUIT DIAGRAM
  ____________________

           _________________________________
          | OLED-DISPLAY 128x64 SPI SSD1309 |
          |____GND_VCC_SCL_SDA_RES_DC_CS____|
                |   |   |   |   |   |   |
       _________|___|___|___|___|___|___|________
      |        GND VCC 15  16  A1  A2  GND       |
      |                        19  20            |
      |                        PF6 PF5           |
      |                                          |
      |            ARDUINO PRO MICRO             |
      |                                          |
      |__GND__2___8___3___0___1___5___7___6___9__|
          |   |   |   |   |   |   |   |   |   |
          |   |   |   |   |   |   |   |   |   |
          |   F   |   7---8---9---+   |   |   |
          |___|   |   |   |   |       |   |   |      4x4 Keyboard
                  E---4---5---6-------+   |   |   (F-key on interuptable
                  |   |   |   |           |   |  pin to enable sleep mode)
                  N---1---2---3-----------+   |
                  |   |   |   |               |
                  X---0---.---#---------------+

      (with LIPO-Battery):

               _______/ _______
              |  OnOff-Switch  |
              |   __________   |        __
              |  |          |  |       |
         +----+--|BATT+  IN+|--+---VCC-|
        _|_      |          |          | Arduino
         =       |          |          | Pro Micro
         +-------|BATT-  IN-|------GND-|
                 |__________|          |__
       LIPO      LIPO Battery
       Battery   Charger (TP4056)

  ____________________

   ASCII TABLE:
  ____________________

      DEC     |  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
          HEX |  0 1 2 3 4 5 6 7 8 9 a b c d e f
      ------------------------------------------
      032 20  |    ! " # $ % & ' ( ) * + , - . /
      048 30  |  0 1 2 3 4 5 6 7 8 9 : ; < = > ?
      064 40  |  @ A B C D E F G H I J K L M N O
      080 50  |  P Q R S T U V W X Y Z [ \ ] ^ _
      096 60  |  ` a b c d e f g h i j k l m n o
      112 70  |  p q r s t u v w x y z { | } ~

  ____________________

   PHYSICAL CONSTANTS
  ____________________

      Constant      ID  Name
      365.2425      A   Gregorian year
      5.291772E-11  Ao  Bohr radius
      384.4E6       Am  Semi-major axis of the Moon's orbit
      1.495979E11   Ae  Semi-major axis of the Earth's orbit
      2.997942E8    c   Speed of light
      3.741772E-16  C1  First radiation constant
      0.01438777    C2  Second radiation constant
      1.602177E-19  e   Electron charge
      96485.34      F   Faraday constant
      2.502908      Fa  Feigenbaum's alpha
      4.669202      Fd  Feigenbaum's delta
      9.80665       g   Standard earth accelleration
      6.674083E-11  G   Newtonian constant of gravitation
      7.748092E-5   Go  Conductance quantum
      0.9159656     Gc  Catalan's constant
      -2.002232     Ge  Lande's electron g-factor
      6.626069E-34  h   Planck constant
      1.38065E-23   k   Boltzmann constant
      4.835979E14   Kj  Josephson constant
      1.616199      lP  Planck length
      9.109383E-31  me  Electron mass
      7.349E22      mM  Mass of the Moon
      1.674927E-27  mn  Neutron mass
      1.672622E-27  mp  Proton mass
      2.17651E-8    mP  Planck mass
      1.660539E-27  mu  Atomic mass unit
      1.492417E-10  Muc Energy equivalent of atomic mass unit
      1.883541E-28  mm  Muon mass
      1.9891E30     mS  Mass of the Sun
      5.9736E24     mE  Mass of the Earth
      6.022141E23   NA  Avogadro's number
      101325        po  Standard atmospheric pressure
      1.875546E-18  qP  Planck charge
      8.314472      R   Molar gas constant
      2.81794E-15   re  Electron radius
      25812.81      RK  Von Klitzing constant
      1.73753E6     RM  Mean radius of the Moon
      1.097373E7    Ryd Rydberg constant
      6.96E8        rS  Mean radius of the Sun
      6.37101E6     rE  Mean radius of the Earth
      273.15        To  Standard temperature
      5.39106E-44   tP  Planck time
      1.416833E-32  TP- Planck temperature
      0.02241397    Vm  Molar volume of an ideal gas
      376.7303      Zo  Impedance of vacuum
      7.297353E-3   _A  Fine structure constant
      0.5772157     _GE Euler-Mascheroni constant
      2.675222E8    _GP Proton gyromagnetic ratio
      8.854188E-12  _Eo Electric constant or vacuum permitivity
      2.42631E-12   _Le Compton wavelength of the electron
      1.319591E-15  _Ln Compton wavelength of the neutron
      1.32141E-15   _Lp Compton wavelength of the proton
      1.256673E-6   _mo Magnetic constant or vacuum permeability
      9.274009E-24  _mB Bohr's magneton
      -9.284764E-24 _me Electron magnetic moment
      -9.662364E-27 _mn Neutron magnetic moment
      1.410607E-26  _mp Proton magnetic moment
      5.050783E-27  _mu Nuclear magneton
      -4.490448E-26 _mm Muon magnetic moment
      5.670373E-8   _SB Stefan-Boltzmann constant
      1.618034      _P  Golden ratio
      2.067834E-15  _Po Magnetic flux quantum
