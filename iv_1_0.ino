/*
  TODO
    atan(1E36)
    clean up
    another plotting app
    game
    about
    repeat last command

    functions left:
      from quart: rcl sto rotup lastx stacklift prgfmt
      from dm42: setradix(, or .) signum show int/ sqr
    matrix


  xor
  type
  ! c@ c! cmove fill erase
  begin-while-repeat
  for-next

  ." " ... output string
  i ... loop word/variable
  DO -sequence- LOOP ... loops i from X to Y-1
  VARIABLE v ... define variable v (actually pointer)
     ? ... outputs variable (equal to: @ .)
     n constant c ... save n to constant c (c pushes n to stack)
     ALLOT ... array memory allocation

  ----v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8

  ____________________

  Welcome to Ivee (IV) - A Powerful Programable RPN Calculator based on FORTH
  Version 1.0, (c) 2020 by deetee/zooxo
  This software is covered by the 3-clause BSD license.
  See also: https://github.com/zooxo/iv and https://youtu.be/m1aFRhqvuLM
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
  - Dictionary of all commands (sorted), words and programs
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
             5 OUT  6 UP              4 E  5 F
      1 NEW  2 IN   3 DOWN            1 B  2 C    3 D
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

*/


// ***** I N C L U D E S

#include <avr/power.h> // Needed for power management
#include <avr/sleep.h> // Needed for sleeping
#include <EEPROM.h> // For saving data to EEPROM


// ***** F O N T S
#define FONT4 4
//#define FONT5 5
#define FONT6 6

// BIGNUMBERFONT 6x8
#define FONTBIGWIDTH 6
#define FONTOFFSETBIG '-'
const byte fontbig [] PROGMEM = {
  0x00, 0x08, 0x08, 0x08, 0x08, 0x00, // -
  0x60, 0x60, 0x00, 0x00, 0x00, 0x00, // .
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // / space
  0x7f, 0x7f, 0x41, 0x41, 0x7f, 0x7f, // 0
  0x40, 0x42, 0x7f, 0x7f, 0x40, 0x40, // 1
  0x79, 0x79, 0x49, 0x49, 0x4f, 0x4f, // 2
  0x41, 0x49, 0x49, 0x49, 0x7f, 0x7f, // 3
  0x0f, 0x0f, 0x08, 0x08, 0x7f, 0x7f, // 4
  0x4f, 0x4f, 0x49, 0x49, 0x79, 0x79, // 5
  0x7f, 0x7f, 0x49, 0x49, 0x79, 0x78, // 6
  0x03, 0x03, 0x01, 0x01, 0x7f, 0x7f, // 7
  0x7f, 0x7f, 0x49, 0x49, 0x7f, 0x7f, // 8
  0x0f, 0x4f, 0x49, 0x49, 0x7f, 0x7f, // 9
  0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
};


// NORMAL FONT 4x8
#define FONTWIDTH 4
#define FONTOFFSET ' '
const byte font4 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, // space
  0x00, 0x5f, 0x00, 0x00, // !
  0x0b, 0x07, 0x0b, 0x07, // "
  //0x3e, 0x14, 0x14, 0x3e, // #
  0x6d, 0x11, 0x11, 0x6d, // ; # mean value
  0x2e, 0x6a, 0x2b, 0x3a, // $
  0x26, 0x12, 0x48, 0x64, // %
  0x76, 0x49, 0x76, 0x60, // &
  //0x00, 0x0b, 0x07, 0x00, // '
  0x22, 0x72, 0x27, 0x22, // ' leftright
  0x7f, 0x41, 0x41, 0x00, // (
  0x00, 0x41, 0x41, 0x7f, // )
  0x24, 0x18, 0x18, 0x24, // *
  0x08, 0x1c, 0x08, 0x00, // +
  //0x00, 0x58, 0x38, 0x00, // ,
  0x10, 0x7f, 0x01, 0x01, // , squareroot
  0x08, 0x08, 0x08, 0x08, // -
  0x00, 0x60, 0x60, 0x00, // .
  0x20, 0x10, 0x08, 0x04, // /
  0x7f, 0x41, 0x41, 0x7f, // 0
  0x00, 0x02, 0x7f, 0x00, // 1
  0x79, 0x49, 0x49, 0x4f, // 2
  0x41, 0x49, 0x49, 0x7f, // 3
  0x0f, 0x08, 0x08, 0x7f, // 4
  0x4f, 0x49, 0x49, 0x79, // 5
  0x7f, 0x49, 0x49, 0x79, // 6
  0x03, 0x01, 0x01, 0x7f, // 7
  0x7f, 0x49, 0x49, 0x7f, // 8
  0x4f, 0x49, 0x49, 0x7f, // 9
  0x00, 0x36, 0x36, 0x00, // :
  0x00, 0x5b, 0x3b, 0x00, // ;
  0x08, 0x14, 0x22, 0x41, // <
  0x14, 0x14, 0x14, 0x14, // =
  0x41, 0x22, 0x14, 0x08, // >
  0x03, 0x59, 0x09, 0x0f, // ?
  0x3e, 0x41, 0x5d, 0x5e, // @
  0x7f, 0x09, 0x09, 0x7f, // A
  0x7f, 0x49, 0x4f, 0x78, // B
  0x7f, 0x41, 0x41, 0x40, // C
  0x41, 0x7F, 0x41, 0x7F, // D
  0x7F, 0x49, 0x49, 0x41, // E
  0x7F, 0x09, 0x09, 0x01, // F
  0x7f, 0x41, 0x49, 0x79, // G
  0x7F, 0x08, 0x08, 0x7F, // H
  0x41, 0x7f, 0x41, 0x40, // I
  0x60, 0x40, 0x40, 0x7f, // J
  0x7F, 0x08, 0x0f, 0x78, // K
  0x7F, 0x40, 0x40, 0x40, // L
  0x7F, 0x07, 0x07, 0x7F, // M
  0x7F, 0x06, 0x0c, 0x7F, // N
  0x7f, 0x41, 0x41, 0x7f, // O
  0x7F, 0x09, 0x09, 0x0f, // P
  0x7f, 0x41, 0x61, 0x7f, // Q
  0x7F, 0x09, 0x79, 0x4f, // R
  0x4f, 0x49, 0x49, 0x78, // S
  0x01, 0x7f, 0x01, 0x01, // T
  0x7F, 0x40, 0x40, 0x7F, // U
  0x1F, 0x70, 0x70, 0x1F, // V
  0x7F, 0x70, 0x70, 0x7F, // W
  0x77, 0x08, 0x08, 0x77, // X
  0x4f, 0x48, 0x48, 0x7f, // Y
  0x71, 0x49, 0x49, 0x47, // Z
  //0x7f, 0x41, 0x41, 0x00, // [
  //0x7f, 0x47, 0x47, 0x7f, // [ upper
  0x02, 0x7f, 0x7f, 0x02, // [ arrow up
  //0x04, 0x08, 0x10, 0x20, // backslash
  0x2a, 0x1c, 0x1c, 0x2a, // backslash sun
  //0x00, 0x41, 0x41, 0x7f, // ]
  //0x7f, 0x71, 0x71, 0x7f, // ] lower
  0x20, 0x7f, 0x7f, 0x20, // ] arrow down
  0x02, 0x01, 0x01, 0x02, // ^
  0x40, 0x40, 0x40, 0x40, // _
  //0x00, 0x07, 0x0b, 0x00, // `
  0x3c, 0x20, 0x28, 0x20, // ` angle
  0x70, 0x54, 0x54, 0x7c, // a
  0x7F, 0x44, 0x44, 0x7c, // b
  0x7c, 0x44, 0x44, 0x44, // c
  0x7c, 0x44, 0x44, 0x7F, // d
  0x7c, 0x54, 0x54, 0x5c, // e
  0x04, 0x7f, 0x05, 0x01, // f
  0x5c, 0x54, 0x54, 0x7c, // g
  0x7F, 0x04, 0x04, 0x7c, // h
  0x40, 0x44, 0x7d, 0x40, // i
  0x40, 0x40, 0x44, 0x7d, // j
  0x7f, 0x10, 0x1c, 0x70, // k
  0x01, 0x7f, 0x40, 0x40, // l
  0x7C, 0x0c, 0x0c, 0x7c, // m
  0x7C, 0x04, 0x04, 0x7c, // n
  0x7c, 0x44, 0x44, 0x7c, // o
  0x7c, 0x14, 0x14, 0x1c, // p
  0x1c, 0x14, 0x14, 0x7c, // q
  0x7C, 0x04, 0x04, 0x04, // r
  0x5c, 0x54, 0x54, 0x74, // s
  0x04, 0x7F, 0x44, 0x40, // t
  0x7C, 0x40, 0x40, 0x7C, // u
  0x1c, 0x60, 0x60, 0x1c, // v
  0x7C, 0x60, 0x60, 0x7C, // w
  0x6c, 0x10, 0x10, 0x6c, // x
  0x5c, 0x50, 0x50, 0x7c, // y
  0x74, 0x54, 0x54, 0x5c, // z
  0x08, 0x1c, 0x3e, 0x7f, // { left arrow
  0x00, 0x7f, 0x00, 0x00, // |
  0x7f, 0x3e, 0x1c, 0x08, // } right arrow
  //0x04, 0x02, 0x04, 0x02, // ~
  0x77, 0x5d, 0x49, 0x63, // ~ sum
  0x55, 0x2a, 0x55, 0x2a  // del grey rectangle
};


// *****  D I S P L A Y

// DEFINES
#define SCREENBYTES 256 // Number of bytes to address SCREEN (SCREENWIDTH x SCREENHEIGHT)/8
#define EEBRIGHTNESS   0 // EEPROM address for brightness

// PINS, PORTS
// Display
#define CS_PORT PORTD   // CS port
#define CS_BIT PORTD6   // CS physical bit number
#define PIN_DC 20       // DC pin number
#define DC_PORT PORTF   // DC port
#define DC_BIT PORTF5   // DC physical bit number
#define PIN_RST 19       // RST pin number
#define RST_PORT PORTF  // RST port
#define RST_BIT PORTF6  // RST physical bit number
#define SPI_MISO_PORT PORTB
#define SPI_MISO_BIT PORTB3
#define SPI_MOSI_PORT PORTB
#define SPI_MOSI_BIT PORTB2
#define SPI_SCK_PORT PORTB
#define SPI_SCK_BIT PORTB1
#define SPI_SS_PORT PORTB
#define SPI_SS_BIT PORTB0

// VARIABLES
static byte dbuf[SCREENBYTES]; // Buffer for virtual screen (costs 256 bytes of dynamic memory)
static byte eachframemillis, thisframestart, lastframedurationms; // Framing times
static boolean justrendered; // True if frame was just rendered
static boolean isscreensave = false; // True if screensaver is active
static long powertimestamp = 0; // Needed for timing of power manangement
static byte brightness = EEPROM[EEBRIGHTNESS]; // Brightness

// SUBPROGRAMS
void SPItransfer(byte data) { // Write to the SPI bus (MOSI pin)
  SPDR = data;
  asm volatile("nop"); // Tiny delay before wait
  while (!(SPSR & _BV(SPIF))) {} // Wait for byte to be sent
}

static void ScreenCommandMode(void) { // Set screen to command mode
  bitClear(DC_PORT, DC_BIT);
}

static void ScreenDataMode(void) { // Set screen to data mode
  bitSet(DC_PORT, DC_BIT);
}

static void bootpins(void) { // Declare and boot port pins
  DDRB  |= _BV(SPI_MOSI_BIT) | _BV(SPI_SCK_BIT) | _BV(SPI_SS_BIT);
  PORTD |= _BV(CS_BIT); // Port D
  PORTD &= ~(_BV(RST_BIT));
  DDRD  |= _BV(RST_BIT) | _BV(CS_BIT) | _BV(DC_BIT);
}

static void bootSPI(void) { // Initialize the SPI interface for the display
  SPCR = _BV(SPE) | _BV(MSTR); // master, mode 0, MSB first, CPU clock / 2 (8MHz)
  SPSR = _BV(SPI2X);
}

const byte PROGMEM ScreenBootProgram[] = { // SSD1306 boot sequence
  // 0xAE, // Display Off
  0xD5, 0xF0, // Set Display Clock Divisor v = 0xF0 - default is 0x80
  // 0xA8, 0x3F, // Set Multiplex Ratio v = 0x3F
  // 0xD3, 0x00, // Set Display Offset v = 0
  // 0x40, // Set Start Line (0)
  0x8D, 0x14, // Charge Pump Setting v = enable (0x14) - default is disabled
  0xA1, // Set Segment Re-map (A0) | (b0001) - default is (b0000)
  0xC8, // Set COM Output Scan Direction
  // 0xDA, 0x12, // Set COM Pins v
  //0x81, 0xCF, // Set Contrast v = 0xCF
  //0x81, 0x00, // Set Contrast v = 0x00
  0xD9, 0xF1, // Set Precharge = 0xF1
  // 0xDB, 0x40, // Set VCom Detect
  // 0xA4, // Entire Display ON
  // 0xA6, // Set normal/inverse display
  0xAF, // Display On
  0x20, 0x00, // Set display mode = horizontal addressing mode (0x00)
  0x21, 0x00, 0x7f, // Set col address range ... needed for SSD1309 controller
  0x22, 0x00, 0x07 // Set page address range ... needed for SSD1309 controller
};

static void bootscreen(void) { // Boot screen - reset the display
  delayshort(5); // Reset pin should be low here - let it stay low a while
  bitSet(RST_PORT, RST_BIT); // Set reset pin high to come out of reset
  delayshort(5); // Wait
  bitClear(CS_PORT, CS_BIT); // Select the display (permanently, since nothing else is using SPI)

  ScreenCommandMode(); // Run customized boot-up command sequence
  for (byte i = 0; i < sizeof(ScreenBootProgram); i++)
    SPItransfer(pgm_read_byte(ScreenBootProgram + i));
  SPItransfer(0x81); SPItransfer(EEPROM[EEBRIGHTNESS]); // Set contrast
  ScreenDataMode();
}

static void screenoff(void) { // Shut down the display
  ScreenCommandMode();
  SPItransfer(0xAE); // Display off
  SPItransfer(0x8D); // Disable charge pump
  SPItransfer(0x10);
  delayshort(100);
  bitClear(RST_PORT, RST_BIT); // Set RST to low (reset state)
}
static void screenon(void) { // Restart display after screenoff
  bootscreen();
}


// ***** K E Y B O A R D

// PINS
#define KEYBOARDCOL1 10 // IV BIG
  #define KEYBOARDCOL2 3
  #define KEYBOARDCOL3 0
  #define KEYBOARDCOL4 1
  #define KEYBOARDROW1 5
  #define KEYBOARDROW2 7
  #define KEYBOARDROW3 8
  #define KEYBOARDROW4 9

/*/
#define KEYBOARDCOL1 8 // IV TINY
#define KEYBOARDCOL2 3
#define KEYBOARDCOL3 0
#define KEYBOARDCOL4 1
#define KEYBOARDROW1 5
#define KEYBOARDROW2 7
#define KEYBOARDROW3 6
#define KEYBOARDROW4 9//*/

// DEFINES
#define MAGICKEYPIN 2 // Pin of magic key
#define KEY1 '?' // SHIFT    1-?  2-7  3-8  4-9
#define KEY2 '7' //          5->  6-4  7-5  8-6
#define KEY3 '8' //          9-= 10-1 11-2 12-3
#define KEY4 '9' //         13-< 14-0 15-: 16-;
#define KEY5 '>' // EE
#define KEY6 '4'
#define KEY7 '5'
#define KEY8 '6'
#define KEY9 '=' // CHS
#define KEY10 '1'
#define KEY11 '2'
#define KEY12 '3'
#define KEY13 '<' // CLX
#define KEY14 '0'
#define KEY15 ':' // DOT
#define KEY16 ';' // #

#define PRINTNOKEY   254 // Only evaluate keys smaller
#define NOPRINTNOKEY 255 // Evaluate keys smaller

// VARIABLES
static byte key = PRINTNOKEY; // Holds entered key
static byte oldkey = PRINTNOKEY; // Holds oldkey - to prevent keyrepeat

// SUBPROGRAMS
static byte getkey() {
  pinMode(MAGICKEYPIN, INPUT_PULLUP);
  if (!digitalRead(MAGICKEYPIN)) return (KEY1); // F-key pressed
  byte pinscol[4] = {KEYBOARDCOL1, KEYBOARDCOL2, KEYBOARDCOL3, KEYBOARDCOL4}; // Pins
  byte pinsrow[4] = {KEYBOARDROW1, KEYBOARDROW2, KEYBOARDROW3, KEYBOARDROW4};
  char k[4][4] = {
    {NULL, KEY2, KEY3, KEY4},
    {KEY5, KEY6, KEY7, KEY8},
    {KEY9, KEY10, KEY11, KEY12},
    {KEY13, KEY14, KEY15, KEY16},
  };
  byte kee = NOPRINTNOKEY;
  for (byte r = 0; r < 4; r++) pinMode(pinsrow[r], INPUT_PULLUP); // Set rows to Vcc
  for (byte c = 0; c < 4; c++) {
    pinMode(pinscol[c], OUTPUT); // Set cols as OUTPUT and to GND
    digitalWrite(pinscol[c], LOW);
    for (byte r = 0; r < 4; r++) if (!digitalRead(pinsrow[r])) kee = (k[r][c]); //Assign key
    digitalWrite(pinscol[c], HIGH); // Reset cols to Vcc and INPUT
  }
  return (kee);
}


// ***** S Y S T E M

// DEFINES
#define SCREENWIDTH 64 // Virtual screen width
#define SCREENHEIGHT 32 // Virtual screen height
#define MAXLIN 4 // Maximum of lines
#define FRAMERATE 15 // Maximal number of screen refreshes per second (>3)
#define SIZES 0x01 // Printing size
#define SIZEM 0x02 // Printing size
#define SIZEL 0x04 // Printing size
#define EECONTRAST 0 // EEPROM address to save brightness (1 byte)


// SUBPROGRAMS

static double _abs(double f) { // Absolute value
  return (f < 0.0 ? -f : f);
}

static void dbuffill(byte n) { // Fill display buffer with pattern
  memset(dbuf, n, SCREENBYTES);
}

static void display(void) { // Print display buffer (64x32) to real screen (128x64)
  for (byte l = 0; l < MAXLIN; l++) { // Four lines
    for (byte k = 0; k < 2; k++) { // Two nibbles (double height)
      for (byte j = 0; j < SCREENWIDTH; j++) {
        byte tmp = expand4bit((dbuf[j + l * SCREENWIDTH] >> (k * 4)) & 0x0f); // Expand 0000abcd
        SPItransfer(tmp); SPItransfer(tmp); // Double width
      }
    }
  }
}

static void setframerate(byte rate) { // Calculate frameduration
  eachframemillis = 1000 / rate;
}

static void setscreencontrast(byte c) { // Set screen contrast
  ScreenCommandMode();
  SPItransfer(0x81);
  SPItransfer(c);
  ScreenDataMode();
  EEPROM.write(EECONTRAST, c);
}

static void idle(void) { // Idle, while waiting for next frame
  SMCR = _BV(SE); // Select idle mode and enable sleeping
  sleep_cpu();
  SMCR = 0; // Disable sleeping
}

static bool nextFrame(void) { // Wait (idle) for next frame
  byte now = (byte) millis(), framedurationms = now - thisframestart;
  if (justrendered) {
    lastframedurationms = framedurationms;
    justrendered = false;
    return false;
  }
  else if (framedurationms < eachframemillis) {
    if (++framedurationms < eachframemillis) idle();
    return false;
  }
  justrendered = true;
  thisframestart = now;
  return true;
}

static byte expand4bit(byte b) { // 0000abcd  Expand 4 bits (lower nibble)
  b = (b | (b << 2)) & 0x33;     // 00ab00cd
  b = (b | (b << 1)) & 0x55;     // 0a0b0c0d
  return (b | (b << 1));         // aabbccdd
}

static void printcat(byte c, byte fnt, boolean bitshift, byte w, byte h, byte x, byte y) {
  // Print char c (one bit shifted down) with width (1, 2, 4), size (1, 2) at position (x, y)
  byte printbitshift = bitshift ? 1 : 0;
  byte fwidth = FONTWIDTH;
  byte foffset = FONTOFFSET;
  if (fnt != FONT4) {
    fwidth = FONTBIGWIDTH;
    foffset = FONTOFFSETBIG;
    if (c == '.') fwidth = 2; // Dot
  }
  for (byte k = 0; k < h; k++) {
    for (int i = 0; i < fwidth; i++) {
      byte tmp;
      if (fnt == FONT4) tmp = pgm_read_byte(font4 + FONTWIDTH * (c - foffset) + i) << printbitshift;
      else tmp = pgm_read_byte(fontbig + FONTBIGWIDTH * (c - foffset) + i) << printbitshift;
      if (h == 2) tmp = expand4bit(tmp >> (4 * k) & 0x0f);
      for (byte j = 0; j < w; j++) dbuf[x + (w * i + j) + (y + k) * SCREENWIDTH] = tmp;
    }
  }
}

static void printsat(char * s, boolean bitshift, byte w, byte h, byte x, byte y) { // Print sized string s at (x|y)
  byte i = 0;
  while (s[i]) printcat(s[i++], FONT4, bitshift, w, h, x + i * (FONTWIDTH + 1) * w , y );
}

static void printpixel(byte x, byte y) { // Print pixel at x,y
  dbuf[x + (y / 8)*SCREENWIDTH] |= 1 << (y % 8);
}
static void printhline(byte y) { // Print horizontal line
  for (byte i = 0; i < SCREENWIDTH; i++) printpixel(i, y);
}
static void printvline(byte x) { // Print horizontal line
  for (byte i = 0; i < SCREENHEIGHT; i++) printpixel(x, i);
}

static void delayshort(byte ms) { // Delay (with timer) in ms with 8 bit duration
  long t = millis();
  while ((byte)(millis() - t) < ms) ;
}
static void delaylong(byte nr) { // Delay nr quarters of a second
  for (byte i = 0; i < nr; i++) delayshort(250);
}

static double pow10(int8_t e) { // Calculates 10 raised to the power of e
  double f = 1.0;
  if (e > 0) while (e--) f *= 10.0;
  else while (e++) f /= 10.0;
  return (f);
}

static void wakeupnow() {} // Dummy wakeup code

static void sleepnow(void) { // Power down
  screenoff(); // Display off only if screensaver didn't
  pinMode(MAGICKEYPIN, INPUT_PULLUP);
  sleep_enable();
  attachInterrupt(MAGICKEYPIN, wakeupnow, CHANGE); // LOW, HIGH, CHANGE, FALLING, RISING
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  // SLEEP ... till SHIFT is pressed //
  sleep_disable();
  detachInterrupt(MAGICKEYPIN);
  bootscreen(); // Display on
  powertimestamp = millis();// Keep awake when active
  delayshort(200);
}

//#define MX0 0
#define MX1 1
#define MX2 2
#define MX3 3
#define MX4 4

static int rawadc() { // Measure Vcc
  power_adc_enable();
  ADMUX = (_BV(REFS0) | _BV(MX4) | _BV(MX3) | _BV(MX2) | _BV(MX1)); // Set voltage bits
  delayshort(2); // Wait for ADMUX setting to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // Measuring
  power_adc_disable();
  return (ADC);
}


// ***** A P P L I C A T I O N

// MACROS
#define _ones(x) ((x)%10)        // Calculates ones unit
#define _tens(x) (((x)/10)%10)   // Calculates tens unit
#define _huns(x) (((x)/100)%10)  // Calculates hundreds unit
#define _tsds(x) (((x)/1000)%10) // Calculates thousands unit

// CONSTANTS
#define DIGITS           8 // Number of digits
#define INDICATOR        6 // X-offset for numbers (room for indicator)
#define TINYNUMBER    1e-8 // Number for rounding to 0
#define ALMOSTZERO   1e-37 // Limits to decide if sci or fix
#define OVERFLOW        36 // Max power of 10 before overflow
#define OVERFLOWEXP     87 // Max power of e before overflow
#define FIXMIN        1e-3 // Limits for fix display guarantee maximal
#define FIXMAX         1e7 //             number of significant digits
#define FIXSCI           3 // Display 3 decimals in scientific view
#define FIXMANT          3 // FIX in 10th-exponent
#define ISF              1 // F-key demanded
#define ISG              2 // G-key demanded
#define FLONGPRESSTIME 350 // Time in ms when f longpress starts
#define MAXSTRBUF       23 // Maximal length of string buffer sbuf[]
#define ALPHABUFSIZE    13 // Maximal size of alpha
#define PRGNAMEMAX       3 // Maximal number of characters of program name
#define PRGSIZEMAX     128 // Max size of prg, prgptr, prgbuf
#define MEMNR           10 // Maximal number of constant memories in EEPROM (slots)
#define EEMEM            3 // Starting EE-address for constants (2x16x4)
#define RAD  ((180.0)/(PI)) // 180/PI
#define DELTAX        1E-4 // Delta for solver
#define INTSTRIPES      10 // Number of Simpson stripes for integrating
#define DARKTIMEMIN      3 // Minimal time for auto display off in 10 x s
#define BDIGITS         20 // Number of displayed digits in business mode

#define C0 (struct data){NULL, NULL,NULL} // Complex NULL

#define MAXCMDI  76 // Number of commands of intrinsic functions
#define MAXCMDB 120 //120 End of builtin commands
#define MAXCMDU 160 //160 End of user commands

// EEPROM addresses
#define EEDARKTIME 1 // EEPROM address for display off time
#define EEBASE     2 // Store base
#define MEMNR     10 // Maximal number of constant memories in EEPROM (slots)
#define EEMEM      3 // Starting EE-address for constants (2xMEMNRx4)
#define EEMEMB    83 // Starting EE-address for base number (8)
#define MENUITEMS 32 // Number of selectable user menu items
#define EEMENU    91 // Start of user menu in EEPROM (MENUITEMS bytes)
#define EEUSTART 123 // EEPROM address of user programs
#define EEUEND   EEPROM.length()
#define EEU (EEUEND-EEUSTART) // Available user memory

// GLOBAL VARIABLES
struct data { // Structure for numbers
  double r, i; // Real, imaginary
  int64_t b; // Integer, base
};

#define DATASTACKSIZE 26 // DATA STACK
struct data ds[DATASTACKSIZE];
static byte dp = 0;

#define ADDRSTACKSIZE 64 // ADDRESS STACK
static int as[ADDRSTACKSIZE];
static byte ap = 0;

byte cl = 0; // CONDITIONAL LEVEL
static int mp; // MEMPOINTER (builtin and user functions)

static char sbuf[MAXSTRBUF]; // Holds string to print
static byte fgm = 0, setfgm = 0; // F-key variables
static byte decimals = 0; // Number of decimals entered (input after decimal dot)
static boolean isdot = false; // True if dot was pressed and decimals will be entered
static boolean isnewnumber = true; // True if stack has to be lifted before entering a new number
static boolean isprintscreen = true; // True, if screen should be printed
static boolean darkscreen = false; // Shows empty dbuf, if true
static boolean ispolar = false; // Shows imaginary number in polar format (else rectangulsr)
static boolean isfloated = false; // True, if data stack was floated
boolean isgetkey = false; // Needed for getkey function
static char alpha[ALPHABUFSIZE] = {NULL}; // String buffer (alpha) for user text output
static boolean isprintalpha = false; // Print alpha if true
static long timestamp; // Timestamp for f longpress
static boolean freleased = false; // Used for releasing longpressed f-key
static byte darktime; // Time of inactivity for dark screen (in 10 x s)
static long durationtimestamp = millis();
static byte pause = 0; // Pause time in n * 250 ms
static byte base = 0; // BASE 0-sci 2-bin 6-oct 10-business 16-hex
static boolean isAF; //Next keypress is hexA ... hexF
static int breakmp; // Holds memory pointer while break
static boolean isprintinput = false; // True, if inputnumber is printed

static byte select; // Selected options
static boolean isdict = false; // True for dict browsing
static boolean ismenu = false; // True, if menu was demanded
static boolean issetusr = false; // True if dict is used for setting usr menu
static byte setusrselect; // Stores selected cmd value to store
static boolean ismenusetusr; // True for choosing user menu place
static boolean istorch; // Shows full display it true

static byte prgselect = 0; // Number of selected program
static boolean isprgselect = false; // Used for selecting program
static boolean isprgedit = false; // True, if program is editet
static boolean isprgdict = false, isprgmenu = false, isprgnew = false;
static boolean isprgeditfirst = false;
static int sou; // Size of user programs
static byte nou; // Number of user programs
static byte prgbuf[PRGSIZEMAX], oldprgbuflen; // Program buffer for fast editing
static int prgaddr; // EEPROM address of actual program
static byte prgbuflen; // Size of program in program buffer
static byte prgeditstart = 0;
static boolean isprgrename = false; // True if program should be renamed
static byte renamenr = 0; // Stores selected prg value to rename

static byte cycles; // Solver cycles
static double x0, x1, f0; // Old and new solve-value
static boolean issolve = false, isint = false; // True if solving or integrating is demanded
static double inta, intb, intdelta, intx, intf; // INT variables

static double plot[SCREENWIDTH]; // Y-values of plot graph
static double plota, plotb, plotd, ymax, ymin; // Variables used for plotting
static boolean isplot = false, isplotcalc = false; // True if plotting or plot calculation is demanded

static byte msgnr = 0; // MESSAGES
#define MSGASK      0
#define MSGDICT     1
#define MSGMENU     2
#define MSGKEY      3
#define MSGRUN      4
#define MSGOVERFLOW 5
#define MSGNEST     6
#define MSGSAVE     7
const char m0[] PROGMEM = "?";
const char m1[] PROGMEM = "DICT";
const char m2[] PROGMEM = "MENU";
const char m3[] PROGMEM = "KEY?";
const char m4[] PROGMEM = "RUN";
const char m5[] PROGMEM = "OVERFLOW";
const char m6[] PROGMEM = "NEST ERROR";
const char m7[] PROGMEM = "SAVE ERROR";
const char* const msg[] PROGMEM = {
  m0, m1, m2, m3, m4, m5, m6, m7
};

// Command code defines
#define _0 0 // Intrinsic commands
#define _1 1
#define _2 2
#define _3 3
#define _4 4
#define _5 5
#define _6 6
#define _7 7
#define _8 8
#define _9 9
#define _DOT 10
#define _DUP 11
#define _DROP 12
#define _NEG 13
#define _E 14
#define _CMPLX 16
#define _RCL 17
#define _SUB 19
#define _MULT 22
#define _DIV 25
#define _ADD 27
#define _SWAP 30
#define _STO 33
#define _BASE 40
#define _PICK 45
#define _ROT 46
#define _LT 48
#define _EQ 49
#define _NE 50
#define _GT 51
#define _NAND 52
#define _ADDDUR 53
#define _PAUSE 54
#define _INT 55
#define _BEGIN 58
#define _UNTIL 59
#define _IF 61
#define _ELSE 62
#define _THEN 63
#define _ISREAL 68
#define _PI 71
#define _INV 72
#define _SIN 73
#define _EXP 74
#define _LN 75
#define _BUS MAXCMDI+0 // Builtin commands (mem)
#define _HEX MAXCMDI+1
#define _AND MAXCMDI+2
#define _NOT MAXCMDI+3
#define _OR MAXCMDI+4
#define _OVER MAXCMDI+5
#define _ABS MAXCMDI+6
#define _SQRT MAXCMDI+7
#define _COS MAXCMDI+8
#define _TAN MAXCMDI+9
#define _POW MAXCMDI+10
#define _PWR10 MAXCMDI+11
#define _LOG MAXCMDI+12
#define _ASIN MAXCMDI+13
#define _ACOS MAXCMDI+14
#define _ATAN MAXCMDI+15
#define _SINH MAXCMDI+16
#define _COSH MAXCMDI+17
#define _TANH MAXCMDI+18
#define _ASINH MAXCMDI+19
#define _ACOSH MAXCMDI+20
#define _ATANH MAXCMDI+21
#define _GAMMALN MAXCMDI+22
#define _HMS2H MAXCMDI+23
#define _H2HMS MAXCMDI+24
#define _PV MAXCMDI+25
#define _ND MAXCMDI+26
#define _QE MAXCMDI+27
#define _CLOCK MAXCMDI+28
#define _CLRSUM MAXCMDI+29
#define _SUM MAXCMDI+30
#define _SUMSUB MAXCMDI+31
#define _STAT MAXCMDI+32
#define _LR MAXCMDI+33
#define _PERCENT MAXCMDI+34
#define _PERCENTDELTA MAXCMDI+35
#define _FRAC MAXCMDI+36
#define _DEGRAD MAXCMDI+37
#define _CF MAXCMDI+38
#define _KMMI MAXCMDI+39
#define _MFT MAXCMDI+40
#define _CMIN MAXCMDI+41
#define _KGLBS MAXCMDI+42
#define _LGAL MAXCMDI+43
#define _END 255 // Function delimiter

// Builtin functions (mem)
const byte mem[] PROGMEM = {
  _END, // Necessary to prevent function starting with mp = 0
  _1, _0, _BASE, _END, //0 BUSINESS
  _1, _6, _BASE, _END, //1 HEX
  _NAND, _DUP, _NAND, _END, //2 AND
  _DUP, _NAND, _END, //3 NOT
  _DUP, _NAND, _SWAP, _DUP, _NAND, _NAND, _END, //4 OR
  _SWAP, _DUP, _ROT, _ROT, _END, //5 OVER
  _DUP, _0, _LT, _IF, _NEG, _THEN, _END, //6 ABS
  _DUP, _0, _EQ, _IF, _DROP, _0, _ELSE, _LN, _2, _DIV, _EXP, _THEN, _END, //7 SQRT sqrt(z)=exp(2*ln(z))
  //_ISREAL, _1, _EQ, _IF, _9, _0, _ADD, _ELSE, _PI, _2, _DIV, _ADD, _THEN, _SIN, _END, //8 COS cos(x)=sqrt(1-sin(z)*sin(z)) cos(x)=sin(x+90)
  _ISREAL, _1, _EQ, _IF, _9, _0, _SWAP, _SUB, _ELSE, _PI, _2, _DIV, _ADD, _THEN, _SIN, _END, //8 COS cos(x)=sqrt(1-sin(z)*sin(z)) cos(x)=sin(90-x)
  _DUP, _SIN, _SWAP, _COS, _DIV, _END, //9 TAN tan(z)=sin(z)/cos(z)
  _SWAP, _LN, _MULT, _EXP, _END, //10 POW a^b=exp(b*ln(a))
  _1, _SWAP, _E, _END, //11 POW10
  _LN, _1, _0, _LN, _DIV, _END, //12 LOG log(z)=ln(z)/ln(10)

  _DUP, _DUP, _DUP, _MULT, _NEG, _1, _ADD, _SQRT, //13 ASIN: asin(z) = -i*ln(i*z+sqrt(1-z*z))
  _SWAP, _0, _DUP, _1, _CMPLX, _MULT, _ADD, _LN, _0, _DUP, _1, _CMPLX, _NEG, _MULT,
  _SWAP, _ISREAL, _1, _EQ, _IF, _DROP, _1, _8, _0, _MULT, _PI, _DIV, // *RAD - if input was real
  _ISREAL, _1, _EQ, _IF, _ELSE, _CMPLX, _DROP, _THEN, // if result is imaginary - set im to 0
  _ELSE, _DROP, _THEN, _END,

  _DUP, _ASIN, _NEG, //14 ACOS acos(z)=PI/2-asin(z)
  _SWAP, _ISREAL, _1, _EQ, _IF, _DROP, _9, _0, _ADD, _ELSE, // +90 - if input was real
  _DROP, _PI, _2, _DIV, _ADD, _THEN, _END, // +PI/2 - if input was complex

  _DUP, _DUP, _MULT, _1, _ADD, _SQRT, _INV, _MULT, _ASIN, _END, //15 ATAN: atan(z)=asin(z/(sqrt(1+z*z)))

  _EXP, _DUP, _INV, _NEG, _ADD, _2, _DIV, _END, //16 SINH sinh(z)=(exp(z)-exp(-z))/2
  _EXP, _DUP, _INV, _ADD, _2, _DIV, _END, //17 COSH cosh(z)=(exp(z)+exp(-z))/2
  _DUP, _SINH, _SWAP, _COSH, _DIV, _END, //18 TANH tanh(z)=sinh(z)/cosh(z)
  _DUP, _DUP, _MULT, _1, _ADD, _SQRT, _ADD, _LN, _END, //19 ASINH asinh(x)=ln(x+sqrt(x*x+1))
  _DUP, _DUP, _MULT, _1, _SUB, _SQRT, _ADD, _LN, _END, //20 ACOSH acosh(z)=ln(z+sqrt(z*z-1))
  _DUP, _1, _ADD, _SWAP, _NEG, _1, _ADD, _DIV, _SQRT, _LN, _END, //21 ATANH atanh(z)=ln(sqrt((1+z)/(1-z)))

  _1, _ADD, _DUP, _DUP, _DUP, _DUP, _1, _2, _MULT, //22 GAMMALN: ln!=(ln(2*PI)-ln(z))/2+z*(ln(z+1/(12*z-1/10/z))-1)
  _SWAP, _1, _0, _MULT, _INV, _SUB, _INV, _ADD, _LN, _1, _SUB, _MULT,
  _SWAP, _LN, _NEG, _2, _PI, _MULT, _LN, _ADD, _2, _DIV, _ADD, _END,

  _DOT, _0, _0, _0, _0, _0, _1, _ADD,//23 HMS2H - round up to prevent leaps
  _DUP, _DUP, _INT, _SWAP, _OVER, _SUB, _1, _0, _0, _MULT, _INT, // hh mm
  _ROT, _3, _PICK, _SUB, _1, _0, _0, _MULT, _OVER, _SUB, _1, _0, _0, _MULT, // ss
  _3, _6, _0, _0, _DIV, _SWAP, _6, _0, _DIV, _ADD, _ADD, _END,// ->s ->h

  _DUP, _3, _6, _0, _0, _MULT, _DUP, _ROT, _INT, //24 H2HMS - h->s
  _SWAP, _OVER, _3, _6, _0, _0, _MULT, _SUB, _6, _0, _DIV, _INT, // hh mm
  _ROT, _OVER, _6, _0, _MULT, _SUB, _3, _PICK, _3, _6, _0, _0, _MULT, _SUB, // ss
  _1, _0, _0, _0, _0, _DIV, _SWAP, _1, _0, _0, _DIV, _ADD, _ADD, _END, // hh.mmss

  _OVER, _1, _ADD, _SWAP, _POW, _DUP, _1, _SUB, _SWAP, _DIV, _SWAP, _DIV, _END, //25 PV PV(i,n)=((1+i)^n-1)/(1+i)^n/i

  _DUP, _DUP, _DUP, _DUP, _MULT, _MULT, _DOT, _0, _7, _MULT, //26 ND
  _SWAP, _1, _DOT, _6, _MULT, _NEG, _ADD, _EXP, _1, _ADD, _INV, _SWAP,
  _DUP, _MULT, _NEG, _2, _DIV, _EXP, _2, _PI, _MULT, _SQRT, _INV, _MULT, _END,

  _OVER, _2, _DIV, _DUP, _MULT, _SWAP, _SUB, _SQRT, _SWAP, _2, _DIV, _NEG, _SWAP, //27 QE x12=-p/2+-sqrt(p*p/4-q)
  _OVER, _OVER, _SUB, _ROT, _ROT, _ADD, _END,

  _DUP, _ADDDUR, _DROP, //28 CLOCK - Reset duration
  _BEGIN, _HMS2H, _3, _6, _0, _0, _0, _0, _0, _MULT, _ADDDUR, // hms to ms and add duration
  _1, _SUB, // Time correction (in ms) ...0
  _3, _6, _0, _0, _0, _0, _0, _DIV, _H2HMS, // Convert ms to hms
  _DUP, _DUP, _DUP, // Copies for display
  _1, _0, _0, _0, _0, _MULT, _INT, // hhmmss
  _SWAP, _1, _0, _0, _MULT, _INT, _1, _0, _0, _MULT, // hhmm00
  _SUB, // Display ss
  _SWAP, _1, _0, _0, _MULT, _INT, // Display hhmm
  _4, _PAUSE, _DROP, _DROP, _0, _UNTIL, _END, // Print and delete display copies

  _0, _DUP, _DUP, _DUP, _DUP, _DUP, //29 CLRSUM
  _5, _STO, _6, _STO, _7, _STO, _8, _STO, _9, _STO, _END,

  _7, _RCL, _1, _ADD, _7, _STO, //30 SUM+ - n
  _DUP, _8, _RCL, _ADD, _8, _STO, // X
  _DUP, _DUP, _MULT, _5, _RCL, _ADD, _5, _STO, // XX
  _OVER, _MULT, _6, _RCL, _ADD, _6, _STO, // XY
  _9, _RCL, _ADD, _9, _STO, _7, _RCL, _END, // Y push(n)

  _7, _RCL, _1, _SUB, _7, _STO, //30 SUM- - n
  _DUP, _8, _RCL, _SWAP, _SUB, _8, _STO, // X
  _DUP, _DUP, _MULT, _5, _RCL, _SWAP, _SUB, _5, _STO, // XX
  _OVER, _MULT, _6, _RCL, _SWAP, _SUB, _6, _STO, // XY
  _9, _RCL, _SWAP, _SUB, _9, _STO, _7, _RCL, _END, // Y

  _8, _RCL, _7, _RCL, _DIV, //32 STAT - mean (X/n)
  _DUP, _DUP, _MULT, _7, _RCL, _MULT, _NEG, _5, _RCL, _ADD, // stddev (XX-n*m^2)/(n-1)
  _7, _RCL, _1, _SUB, _DIV, _SQRT, _SWAP, _END,

  _6, _RCL, _7, _RCL, _MULT, _8, _RCL, _9, _RCL, _MULT, _SUB, //33 L.R. - a
  _5, _RCL, _7, _RCL, _MULT, _8, _RCL, _DUP, _MULT, _SUB, _DIV,
  _DUP, _8, _RCL, _MULT, _NEG, _9, _RCL, _ADD, _7, _RCL, _DIV, _SWAP, _END, // b

  _OVER, _DIV, _1, _0, _0, _MULT, _END, //34 % x/B*100%
  _OVER, _SUB, _OVER, _DIV, _1, _0, _0, _MULT, _END, //35 DELTA% (x-B)/B*100%
  _DUP, _INT, _SUB, _END, //36 FRAC

  _DUP, _PI, _MULT, _1, _8, _0, _DIV, //37 DEG<>RAD
  _SWAP, _1, _8, _0, _MULT, _PI, _DIV, _END,

  _DUP, _1, _DOT, _8, _MULT, _3, _2, _ADD, //38 C<>F
  _SWAP, _3, _2, _SUB, _1, _DOT, _8, _DIV, _END,

  _DUP, _1, _DOT, _6, _0, _9, _3, _4, _4, _DUP, _DUP, //39 KM<>MI
  _ROT, _SWAP, _DIV, _ROT, _ROT, _MULT, _END,

  _DUP, _3, _DOT, _3, _7, _0, _0, _7, _9, _DUP, _DUP, //40 M<>FT
  _ROT, _MULT, _ROT, _ROT, _DIV, _END,


  _DUP, _2, _DOT, _5, _4, _DUP, _DUP, _ROT, _SWAP, _DIV, _ROT, _ROT, _MULT, _END, //41 CM<>IN

  _DUP, _2, _DOT, _2, _0, _4, _6, _2, _3, _DUP, _DUP, //42 KG<>LBS
  //_ROT, _SWAP, _DIV, _ROT, _ROT, _MULT, _END,
  _ROT, _MULT, _ROT, _ROT, _DIV, _END,

  _DUP, _3, _DOT, _7, _8, _5, _4, _1, _2, _DUP, _DUP, //43 L<>GAL
  _ROT, _SWAP, _DIV, _ROT, _ROT, _MULT, _END,

};

// Command names
const char c0[] PROGMEM = "0"; //      PRIMARY KEYS
const char c1[] PROGMEM = "1";
const char c2[] PROGMEM = "2";
const char c3[] PROGMEM = "3";
const char c4[] PROGMEM = "4";
const char c5[] PROGMEM = "5";
const char c6[] PROGMEM = "6";
const char c7[] PROGMEM = "7";
const char c8[] PROGMEM = "8";
const char c9[] PROGMEM = "9";
const char c10[] PROGMEM = ".";
const char c11[] PROGMEM = "DUP"; // #, Enter
const char c12[] PROGMEM = "DRP"; // X, Clear
const char c13[] PROGMEM = "N"; // NEG
const char c14[] PROGMEM = "E"; // EE
const char c15[] PROGMEM = "F"; // Shift
const char c16[] PROGMEM = "CPX"; //0         F-KEYS
const char c17[] PROGMEM = "RCL"; //1
const char c18[] PROGMEM = "fS"; //2 SOLVE
const char c19[] PROGMEM = "-"; //3
const char c20[] PROGMEM = "DIC"; //4
const char c21[] PROGMEM = "fX"; //5
const char c22[] PROGMEM = "*"; //6
const char c23[] PROGMEM = "~+"; //7 SUM+

const char c24[] PROGMEM = "PRG"; //8
const char c25[] PROGMEM = "/"; //9
const char c26[] PROGMEM = "R-P"; //d
const char c27[] PROGMEM = "+"; //x
const char c28[] PROGMEM = "CLR"; //c
const char c29[] PROGMEM = "OVR"; //s
const char c30[] PROGMEM = "SWP"; //e
const char c31[] PROGMEM = "G"; //f
const char c32[] PROGMEM = "BAT"; //0       G-KEYS
const char c33[] PROGMEM = "STO"; //1
const char c34[] PROGMEM = "fI"; //2
const char c35[] PROGMEM = "\\-"; //3
const char c36[] PROGMEM = "USR"; //4
const char c37[] PROGMEM = "fP"; //5
const char c38[] PROGMEM = "\\"; //6
const char c39[] PROGMEM = "~C"; //7 SUMCLR
const char c40[] PROGMEM = "BAS"; //8
const char c41[] PROGMEM = "MOD"; //9
const char c42[] PROGMEM = "CLK"; //d
const char c43[] PROGMEM = "\\+"; //x
const char c44[] PROGMEM = "To"; //c
const char c45[] PROGMEM = "PIC"; //s
const char c46[] PROGMEM = "ROT"; //e
const char c47[] PROGMEM = "OFF"; //f

const char c48[] PROGMEM = "<"; //     OTHER INTRINSIC FUNCTIONS
const char c49[] PROGMEM = "=";
const char c50[] PROGMEM = "<>";
const char c51[] PROGMEM = ">";
const char c52[] PROGMEM = "NAN";
const char c53[] PROGMEM = "+t";
const char c54[] PROGMEM = "PSE";
const char c55[] PROGMEM = "INT";
const char c56[] PROGMEM = "@"; // PEEK
const char c57[] PROGMEM = "!"; // POKE
const char c58[] PROGMEM = "BEG";
const char c59[] PROGMEM = "UNT";
const char c60[] PROGMEM = "EXE";
const char c61[] PROGMEM = "IF";
const char c62[] PROGMEM = "ELS";
const char c63[] PROGMEM = "THN";
const char c64[] PROGMEM = "BRK";
const char c65[] PROGMEM = "KEY";
const char c66[] PROGMEM = "cTX";
const char c67[] PROGMEM = "EMI";
const char c68[] PROGMEM = "re?";
const char c69[] PROGMEM = "nCr";
const char c70[] PROGMEM = "nPr";
const char c71[] PROGMEM = "PI";
const char c72[] PROGMEM = "INV";
const char c73[] PROGMEM = "SIN";
const char c74[] PROGMEM = "EXP";
const char c75[] PROGMEM = "LN";

const char c76[] PROGMEM = "$"; //     BUILTIN FUNCTIONS
const char c77[] PROGMEM = "HEX";
const char c78[] PROGMEM = "AND";
const char c79[] PROGMEM = "NOT";
const char c80[] PROGMEM = "OR";
//const char c81[] PROGMEM = "OVR";
const char c82[] PROGMEM = "ABS";
const char c83[] PROGMEM = ",#"; // SQRT
const char c84[] PROGMEM = "COS";
const char c85[] PROGMEM = "TAN";
const char c86[] PROGMEM = "POW";
const char c87[] PROGMEM = "10^";
const char c88[] PROGMEM = "LOG";
const char c89[] PROGMEM = "aSN";
const char c90[] PROGMEM = "aCS";
const char c91[] PROGMEM = "aTN";
const char c92[] PROGMEM = "SNh";
const char c93[] PROGMEM = "CSh";
const char c94[] PROGMEM = "TNh";
const char c95[] PROGMEM = "aSh";
const char c96[] PROGMEM = "aCh";
const char c97[] PROGMEM = "aTh";
const char c98[] PROGMEM = "LN!";
const char c99[] PROGMEM = "h";
const char c100[] PROGMEM = "hms";
const char c101[] PROGMEM = "PV";
const char c102[] PROGMEM = "ND";
const char c103[] PROGMEM = "QE";
//const char c104[] PROGMEM = "CLK";
//const char c105[] PROGMEM = "~C"; //clrSUM
//const char c106[] PROGMEM = "~+";
const char c107[] PROGMEM = "~-";
const char c108[] PROGMEM = "#"; // STAT
const char c109[] PROGMEM = "LR";
const char c110[] PROGMEM = "%";
const char c111[] PROGMEM = "%C";
const char c112[] PROGMEM = "FRC";
const char c113[] PROGMEM = "'d";
const char c114[] PROGMEM = "'C";
const char c115[] PROGMEM = "'km";
const char c116[] PROGMEM = "'m";
const char c117[] PROGMEM = "'cm";
const char c118[] PROGMEM = "'kg";
const char c119[] PROGMEM = "'l";

const char* const cmd[] PROGMEM = {
  c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20,
  c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31, c32, c33, c34, c35, c36, c37, c38, c39, c40,
  c41, c42, c43, c44, c45, c46, c47, c48, c49, c50, c51, c52, c53, c54, c55, c56, c57, c58, c59, c60,
  c61, c62, c63, c64, c65, c66, c67, c68, c69, c70, c71, c72, c73, c74, c75, c76, c77, c78, c79, c80,
  c29, c82, c83, c84, c85, c86, c87, c88, c89, c90, c91, c92, c93, c94, c95, c96, c97, c98, c99, c100,
  c101, c102, c103, c42, c39, c23, c107, c108, c109, c110, c111, c112, c113, c114, c115, c116,
  c117, c118, c119
};

static byte cmdsort[MAXCMDU]; // Alphabetically sorted commands for DICT


// FUNCTION POINTER ARRAY
static void (*dispatch[])(void) = { // Function pointer array
  &_n0, &_n1, &_n2, &_n3, &_n4, &_n5, &_n6, &_n7, &_n8, &_n9, // Primary keys
  &_dot, &_dup, &_drop, &_neg, &_e, &_keyf,

  &_complex, &_mrcl, &_fnsolve, &_sub, // 0123  FKEY Offset = 16
  &_dict, &_fnfx, &_mul, &_sumadd, // 4567
  &_prgselect, &_div, &_recpol, &_add, // 89dx
  &_clr, &_over, &_swap, &_keyg, // csef
  &_batt, &_msto, &_fnintegrate, &_litdown, // 0123  GKEY Offset = 32
  &_usrset, &_fnplot, &_torch, &_sumclear, // 4567
  &_base, &_mod, &_clock, &_litup, // 89dx
  &_offset, &_pick, &_rot, &_keygoff, // csef

  &_condlt, &_condeq, &_condne, &_condgt, // 48
  &_nand, &_addduration, &_pause, &_integer,
  &_peek, &_poke, &_begin, &_until,
  &_exe, &_condif, &_condelse, &_condthen,

  &_break, &_getkey, &_alphaclear, &_alphaput, // 64
  &_isreal, &_comb, &_perm, &_pi,
  &_inv, &_sin, &_exp, &_ln,

  &_business, &_hex, &_land, &_lnot, // 76 Builtin
  &_lor, &_over, &_absolute, &_sqrt,
  &_cos, &_tan, &_pow, &_pwr10,
  &_log, &_asin, &_acos, &_atan, //88
  &_sinh, &_cosh, &_tanh, &_asinh,
  &_acosh, &_atanh, &_gammaln, &_hms2h,
  &_h2hms, &_pv, &_nd, &_qe, //100
  &_clock, &_sumclear, &_sumadd, &_sumsub,
  &_sumstat, &_sumlr, &_percent, &_percentdelta, //108
  &_frac, &_cvdeg2rad, &_cvc2f, &_cvkm2mi,
  &_cvm2ft, &_cvcm2in, &_cvkg2lbs, &_cvl2gal, //116
};
static void _nop(void) {} // NOP - no operation
static void _n0(void) { // 0
  _numinput(_0);
}
static void _n1(void) { // 1
  _numinput(_1);
}
static void _n2(void) { // 2
  _numinput(_2);
}
static void _n3(void) { // 3
  _numinput(_3);
}
static void _n4(void) { // 4
  _numinput(_4);
}
static void _n5(void) { // 5
  _numinput(_5);
}
static void _n6(void) { // 6
  _numinput(_6);
}
static void _n7(void) { // 7
  _numinput(_7);
}
static void _n8(void) { // 8
  _numinput(_8);
}
static void _n9(void) { // 9
  _numinput(_9);
}
static void _absolute(void) { // ABS
  seekmem(_ABS);
}
static void _acos(void) { // ACOS
  seekmem(_ACOS);
}
static void _acosh(void) { // ACOSH
  seekmem(_ACOSH);
}
static void _add(void) { // ADD + (a+i*b)(c+i*d)=(a+c)+i*(b+d)
  struct data b = dpop(), a = dpop();
  double re = a.r + b.r, im = a.i + b.i;
  if ((int8_t)log10(_abs(re)) > OVERFLOW || (int8_t)log10(_abs(im)) > OVERFLOW)
    msgnr = MSGOVERFLOW;
  else dpush({re, im, a.b + b.b});
}
static void _addduration(void) { // ADD DURATION
  dpushr(dpopr() + (millis() - durationtimestamp));
  durationtimestamp = millis();
}
static void _alphaclear(void) { // ALPHA CLEAR
  alpha[0] = NULL;
  isprintalpha = false;
}
static void _alphaput(void) { // ALPHA PUTCHAR
  byte l = strlen(alpha);
  if (l < ALPHABUFSIZE) {
    alpha[l] = (byte)dpopr(); alpha[l + 1] = NULL;
  }
  isprintalpha = true;
}
static void _asin(void) { // ASIN
  seekmem(_ASIN);
}
static void _asinh(void) { // ASINH
  seekmem(_ASINH);
}
static void _atan(void) { // ATAN
  seekmem(_ATAN);
}
static void _atanh(void) { // ATANH
  seekmem(_ATANH);
}
static void _base(void) { // BASE MODE
  if (base) { // Return from base mode
    B2stack(); base = 0;
  }
  else { // Switch to base mode
    base = dpopr();
    if (base > 1) stack2B(); else base = 0;
  }
  EEPROM[EEBASE] = base;
}
static void _batt(void) { // BATT
  dpushr((double)(1126400L / rawadc()) / 1000.0);
}
static void _begin(void) { // BEGIN
  apush(mp);
}
static void _break(void) { // BREAK
  breakmp = mp; mp = 0;
  isprintscreen = true;
}
static void _business(void) { // BUSINESS MODE
  seekmem(_BUS);
}
static void _ce(void) { // CE
  if (isdot) {
    if (base) { // Drop if in isdot-mode
      dpopb();
      isdot = false; isnewnumber = true;
    }
    else {
      if (decimals)
        dpushr(((long)(dpopr() * pow10(--decimals)) / pow10(decimals)));
      else isdot = false;
    }
  }
  else {
    if (base) {
      int64_t a = dpopb();
      a = a / 100LL / base * 100LL;
      if (!a) isnewnumber = true;
      else dpushb(a);
    }
    else {
      long a = dpopr() / 10.0;
      if (!a) isnewnumber = true;
      else dpushr(a);
    }
  }
}
static void _clock(void) { // CLOCK
  seekmem(_CLOCK);
}
static void _clr(void) { // CLR
  dp = 0;
  _alphaclear();
}
static void _comb(void) { // COMB nCr=n!/r!/(n-r)!=nPr/r!
  byte k = dpushr(dpopr());
  _perm();
  for (byte i = 1; i <= k; i++) dpushr(dpopr() / i);
}
static void _complex(void) { // COMPLEX
  if (!base) {
    if (isreal()) { // Stack -> complex
      if (ispolar) { // Polar
        double b = dpopr(), a = dpopr();
        //dpush({a * sin(b / RAD), a * sin((90.0 + b) / RAD), 0LL});
        //dpush({a * sin(b * PI / 180.0), a * sin((90.0 + b) * PI / 180.0), 0LL});
        //dpush({a * sin(b / RAD), a * sin((90.0 + b) / RAD), 0LL});
        //dpush({a * sin((90.0 + b) / RAD), a * sin(b / RAD), 0LL});
        dpush({a * cos(b / RAD), a * sin(b / RAD), 0LL});
      }
      else { // Rectangular
        double b = dpopr();
        dpush({dpopr(), b, 0LL});
      }
    }
    else { // Complex -> stack
      if (ispolar) { // Polar
        struct data a = dpop();
        dpushr(absolute(a.r, a.i)); dpushr(angle(a.r, a.i));
      }
      else { // Rectangular
        struct data a = dpop();
        dpushr(a.r); dpushr(a.i);
      }
    }
  }
}
static void _condelse(void) { // CONDITION ELSE
  if (!cl) msgnr = MSGNEST; // ELSE without corresponding IF
  else {
    _condseek(); // Seek next THEN
    cl--;
  }
}
static void _condeq(void) { // CONDITION =
  dpushr(dpopr() == dpopr());
}
static void _condgt(void) { // CONDITION >
  dpushr(dpopr() < dpopr());
}

static void _condif(void) { // CONDITION IF
  cl++; // Increment conditional level
  if (!dpopr()) _condseek(); // FALSE-Clause - seek next ELSE or THEN
}
static void _condlt(void) { // CONDITION <
  _condgt();
  dpushr(!dpopr());
}
static void _condne(void) { // CONDITION <>
  _condeq();
  dpushr(!dpopr());
}
static void _condseek(void) { // CONDITION - seek next ELSE or THEN
  boolean isloop = true;
  byte cltmp = 0; // Local conditional level
  while (isloop) {
    byte c = NULL;
    if (mp < sizeof(mem)) c = pgm_read_byte(mem + mp++); // Builtin
    else if (mp < sizeof(mem) + sou) c = EEPROM[mp++ -sizeof(mem) + EEUSTART]; // User
    if (mp >= sizeof(mem) + sou) { // No corresponding ELSE or THEN
      msgnr = MSGNEST;
      isloop = false;
    }
    else if (c == _IF) cltmp++; // Nested IF found
    else if (cltmp && c == _THEN) cltmp--; // Nested IF ended
    else if (!cltmp && (c == _ELSE || c == _THEN)) isloop = false;
  }
}
static void _condthen(void) { // CONDITION THEN
  if (!cl) msgnr = MSGNEST; // THEN without corresponding IF
  else cl--; // Decrement conditional level
}
static void _cvc2f(void) { // CONVERT C>F
  seekmem(_CF);
}
static void _cvcm2in(void) { // CONVERT CM>IN
  seekmem(_CMIN);
}
static void _cvdeg2rad(void) { // CONVERT DEG>RAD
  seekmem(_DEGRAD);
}
static void _cvkg2lbs(void) { // CONVERT KG<>LBS
  seekmem(_KGLBS);
}
static void _cvl2gal(void) { // CONVERT L<>GAL
  seekmem(_LGAL);
}
static void _cvkm2mi(void) { // CONVERT KM>MI
  seekmem(_KMMI);
}
static void _cvm2ft(void) { // CONVERT M>FT
  seekmem(_MFT);
}
static void _cos(void) { // COS
  seekmem(_COS);
}
static void _cosh(void) { // COSH
  seekmem(_COSH);
}
static void _dict(void) { // DICT
  if (!base) {
    select = 0;
    isdict = true;
  }
}
static void _div(void) { // DIV / a/b=a*inv(b)
  if (base) {
    int64_t b = dpopb();
    if (!b) msgnr = MSGOVERFLOW;
    else {
      int64_t m = 1;
      while (b % 10LL == 0) {
        b /= 10LL; m *= 10LL;
      }
      dpushb((dpopb() / b) * 100LL / m);
    }
  }
  else {
    _inv(); _mul();
  }
}
static void _dot(void) { // DOT .
  if (isnewnumber) {
    dpush(C0); // Start new number with 0
    decimals = 0; isnewnumber = false;
  }
  if (base && base != 10) isAF = true; // Enter A~F
  else isdot = true;
}
static void _drop(void) { // DROP, X
  if (isnewnumber && breakmp) { // Return from break and continue program
    mp = breakmp; breakmp = 0;
    delayshort(250); // To prevent interrupting the run with C key
  }
  else if (isnewnumber && dp) dp--; // CLX
  if (!isnewnumber) _ce(); // Clear entry
}
static void _dup(void) { // DUP, #
  if (isnewnumber && dp) dpush(ds[dp - 1]);
}
static void _e(void) { // E
  if (base) dpushb(dpopb() * base * base * base * base); // Expand 4 digits
  else {
    int tmp = dpushr(dpopr());
    if (tmp < -OVERFLOW || tmp > OVERFLOW) msgnr = MSGOVERFLOW;
    else {
      dpushr(pow10(dpopr()));
      _mul();
    }
  }
}
static void _exe(void) { // EXE
  mp = dpopr() + sizeof(mem);
}
static void _exp(void) { // EXP exp(a+jb)=exp(a)*(cos(b)+i*sin(b))
  struct data a = dpop();
  if (a.r > OVERFLOWEXP) msgnr = MSGOVERFLOW;
  else {
    double tmp = texp(a.r);
    dpush({tmp * cos(a.i), tmp * sin(a.i), a.b});
  }
}
static void _fnfx(void) { // FN F(X)
  if (!base) execute(MAXCMDB);
}
static void _fnintegrate(void) { // FN INTEGRATE
  if (!base) {
    _swap(); inta = dpopr();
    intb = dpushr(dpopr());
    intdelta = (intb - inta) / 2 / INTSTRIPES;
    intf = 0.0;
    select = cycles = 0;
    isint = true;
  }
}
void _fnplot() { // FN PLOT
  if (!base) {
    plotb = dpopr(); plota = dpopr();
    plotd = (plotb - plota) / SCREENWIDTH;
    cycles = 0;
    isplot = isplotcalc = true;
  }
}
static void _fnsolve(void) { // FN SOLVE
  if (!base) {
    x0 = dpushr(dpopr());
    select = cycles = 0;
    issolve = true;
  }
}
static void _frac(void) { // FRAC
  seekmem(_FRAC);
}
static void _gammaln(void) { // GAMMALN
  seekmem(_GAMMALN);
}
static void _h2hms(void) { // H2HMS
  seekmem(_H2HMS);
}
static void _hex(void) { // HEX MODE
  seekmem(_HEX);
}
static void _hms2h(void) { // HMS2H
  seekmem(_HMS2H);
}
static void _integer(void) { // INTEGER
  dpushr((long)dpopr());
}
static void _inv(void) { // INV inv(a+jb)=a/(a*a+b*b)-i*b/(a*a+b*b)
  struct data a = dpop();
  if (absolute(a.r, a.i) == 0.0) msgnr = MSGOVERFLOW;
  dpush({1.0 / (a.r + a.i / a.r * a.i), -1.0 / (a.i + a.r / a.i * a.r), 0LL});
}
static void _isreal(void) { // ISREAL?
  dpushr(isreal());
}
static void _getkey(void) { // KEY
  isgetkey = true;
}
static void _keyf(void) { // KEY-F
  fgm = ISF;
  setfgm = 0;
}
static void _keyg(void) { // KEY-G
  fgm = ISG;
  setfgm = 0;
}
static void _keygoff(void) { // KEY-G OFF
  darkscreen = true;
}
static void _lit(byte b) { // LIT
  EEPROM[EEBRIGHTNESS] = b;
  screenoff(); delaylong(12); bootscreen();
  //ScreenCommandMode(); SPItransfer(0x81); SPItransfer(b); ScreenDataMode(); // Set contrast
}
static void _litdown(void) { // LIT DOWN
  byte b = EEPROM[EEBRIGHTNESS];
  _lit(b > 64 ? b - 64 : 0);
}
static void _litup(void) { // LIT UP
  byte b = EEPROM[EEBRIGHTNESS];
  _lit(b < 191 ? b + 64 : 255);
}
static void _ln(void) { // LN ln(a+i*b)=ln(r*exp(i*f))=ln(r)+i*f r=|a+i*b| f=atan(b/a)
  struct data a = dpop();
  if (absolute(a.r, a.i) == 0.0) msgnr = MSGOVERFLOW;
  else dpush({log(absolute(a.r, a.i)), angle(a.r, a.i) / RAD, 0LL});
}
static void _log(void) { // LOG
  seekmem(_LOG);
}
static void _land(void) { // LOGIC AND
  seekmem(_AND);
}
static void _lnot(void) { // LOGIC NOT
  seekmem(_NOT);
}
static void _lor(void) { // LOGIC OR
  seekmem(_OR);
}
static void _mod(void) { // MOD
  if (!base) {
    long b = dpopr();
    dpushr((long)dpopr() % b);
  }
}
static void _mrcl(void) { // MRCL
  _mstorcl(false);
}
static void _msto(void) { // MSTO
  _mstorcl(true);
}
static void _mstorcl(boolean issto) { // MRCL
  if (base)
    if (issto) EEPROM.put(EEMEMB, dpopb());
    else {
      int64_t a;
      EEPROM.get(EEMEMB, a);
      dpushb(a);
    }
  else {
    byte tmp = dpopr();
    if (tmp < MEMNR) {
      struct data a;
      if (issto) {
        a = dpop();
        EEPROM.put(EEMEM + tmp * sizeof(double), a.r);
        EEPROM.put(EEMEM + (tmp + MEMNR) * sizeof(double), a.i);
      }
      else {
        EEPROM.get(EEMEM + tmp * sizeof(double), a.r);
        EEPROM.get(EEMEM + (tmp + MEMNR) * sizeof(double), a.i);
        dpush(a);
      }
    }
  }
}
static void _mul(void) { // MULT * (a+i*b)*(c+i*d)=(a*c-b*d)+i*(b*c+a*d)
  struct data b = dpop(), a = dpop();
  int8_t ac = (int8_t)log10(_abs(a.r)) + (int8_t)log10(_abs(b.r));
  int8_t bd = (int8_t)log10(_abs(a.i)) + (int8_t)log10(_abs(b.i));
  int8_t bc = (int8_t)log10(_abs(a.i)) + (int8_t)log10(_abs(b.r));
  int8_t ad = (int8_t)log10(_abs(a.r)) + (int8_t)log10(_abs(b.i));
  if (ac > OVERFLOW || bd > OVERFLOW || bc > OVERFLOW || ad > OVERFLOW)
    msgnr = MSGOVERFLOW;
  else dpush({a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r, (a.b * b.b) / 100LL});
}
static void _nand(void) { // NAND
  long b = dpopr();
  dpushr(~((long)dpopr() & b));
}
static void _nd(void) { // ND
  seekmem(_ND);
}
static void _neg(void) { // NEGATE
  struct data a = dpop();
  dpush({ -a.r, -a.i, -a.b});
}
static void _numinput(byte k) { // NUM Numeric input (0...9)
  if (isAF) k += 10;
  if (isdot) { // Append decimal
    if (base == 10) {
      int64_t a = dpopb();
      dpushb(a / 100LL * 100LL + a % 10LL * 10LL + k);
    }
    else dpushr(dpopr() + k / pow10(++decimals));
  }
  else if (isnewnumber) dpush({k, 0.0, k * 100}); // Push new numeral
  else if (base) dpushb(((dpopb() / 100) * base + k) * 100); // Append numeral
  else dpushr(dpopr() * 10 + k); // Append numeral
  isnewnumber = isAF = false;
}
static void _offset(void) { // OFF Time Setting
  darktime = dpopr();
  limitdarktime();
  EEPROM[EEDARKTIME] = darktime;
}
static void _over(void) { // OVER
  seekmem(_OVER);
}
static void _pause(void) { // PAUSE
  isprintscreen = true;
  pause = dpopr();
}
static void _peek(void) { // @ PEEK (address peek)
  int addr = dpopr();
  if (addr < EEUEND - EEUSTART) dpushr(EEPROM[EEUSTART + addr]);
}
static void _percent(void) { // PERCENT
  seekmem(_PERCENT);
}
static void _percentdelta(void) { // PERCENTCHANGE
  seekmem(_PERCENTDELTA);
}
static void _perm(void) { // PERM nPr=n!/(n-r)!
  byte a = dpopr(), b = dpopr();
  a = b - a;
  dpushr(1.0);
  for (byte i = a; i < b; i++) dpushr(dpopr() * (i + 1));
}
static void _pi(void) { // PI
  dpushr(PI);
}
static void _pick(void) { // PICK
  byte n = dpopr();
  if (n >= 1 && n <= dp) dpush(ds[dp - n]);
}
void _recpol() { // Toggle RECtangular <-> POLar view of imaginary numbers
  if (!base) ispolar = ispolar ? false : true;
}
static void _poke(void) { // ! POKE (value address poke)
  int addr = dpopr();
  if (addr < EEUEND - EEUSTART) EEPROM[EEUSTART + addr] = (byte)dpopr();
}
void _pow(void) { // POWER
  seekmem(_POW);
}
static void _prgselect(void) { // PRG SELECT
  if (!base) {
    prgselect = 0;
    isprgselect = true;
  }
}
static void _pv(void) { // PV
  seekmem(_PV);
}
void _pwr10(void) { // POWER10
  seekmem(_PWR10);
}
static void _qe(void) { // QE
  seekmem(_QE);
}
static void _rot(void) { // ROT
  if (dp > 2) {
    struct data a = dpop(), b = dpop(), c = dpop();
    dpush(b); dpush(a); dpush(c);
  }
}
static void _sin(void) { // SIN sin(a+i*b)=sin(a)*cosh(b)+i*cos(a)*sinh(b)
  if (isreal()) dpushr(sin(dpopr() / RAD));
  else {
    struct data a = dpop();
    double e = texp(a.i);
    dpush({sin(a.r) * (e + 1.0 / e) / 2.0, sin(PI / 2 - a.r) * (e - 1.0 / e) / 2.0, 0LL});
  }
}
static void _sinh(void) { // SINH
  seekmem(_SINH);
}
static void _sqrt(void) { // SQRT
  seekmem(_SQRT);
}
static void _sub(void) { // SUB - a-b=a+(-b)
  if (base) {
    int64_t b = dpopb();
    dpushb(dpopb() - b);
  }
  else {
    _neg(); _add();
  }
}
static void _sumadd(void) { // SUM+
  if (!base) seekmem(_SUM);
}
static void _sumclear(void) { // SUM CLEAR
  if (!base) seekmem(_CLRSUM);
}
static void _sumstat(void) { // SUM STAT
  seekmem(_STAT);
}
static void _sumsub(void) { // SUM-
  seekmem(_SUMSUB);
}
static void _sumlr(void) { // SUM L.R.
  seekmem(_LR);
}
static void _swap(void) { // SWAP
  if (dp > 1) {
    struct data a = dpop(), b = dpop();
    dpush(a); dpush(b);
  }
}
static void _tan(void) { // TAN
  seekmem(_TAN);
}
static void _tanh(void) { // TANH
  seekmem(_TANH);
}
static void _torch(void) { // TORCH
  istorch = true;
}
static void _until(void) { // UNTIL
  if (!ap) msgnr = MSGNEST; // No BEGIN for this UNTIL
  else if (dpopr()) apop(); // Go on (delete return address)
  else apush(mp = apop()); // Go back to BEGIN
}
static void _usrset(void) { // USR
  if (!base) {
    select = 0; isdict = issetusr = true;
  }
}


// SUBROUTINES
static void limitdarktime(void) { // Limit darktime to DARKTIMEMIN
  darktime = max(darktime, DARKTIMEMIN);
}

static double texp(double f) { // Calculate exp with Taylor series
  double result = 1.0, frac = 1.0;
  //???//
  for (byte i = 1; _abs(frac) > TINYNUMBER; i++) result += frac *= f / i;
  //for (byte i = 1; frac > TINYNUMBER; i++) result += frac *= f / i;
  //for (byte i = 1; i < 255; i++) result += frac *= f / i;
  //byte i=1; while(i<255) result += frac *= f / i++;
  return (result);
  //return(exp(f));

  //for (byte i = 255; i > 0; i--) result = 1 + f * result / i;
  //return(result);
}

static double _pow10(int8_t e) { // Calculates 10 raised to the power of e
  double f = 1.0;
  if (e > 0) while (e--) f *= 10.0;
  else while (e++) f /= 10.0;
  return (f);
}

static boolean bothzero(double a, double(b)) { // True, if both arguments = 0.0
  return (a == 0.0 && b == 0.0);
}

static double absolute(double a, double b) { // Returns the absolute value of a complex number
  a = _abs(a); b = _abs(b);
  if (a == 0.0) return (b);
  else if (b == 0.0) return (a);
  return (texp(0.5 * (log(a) + log(a + b / a * b)))); // Prevent big arguments
}

static double angle(double a, double b) { // Returns the angle of a complex number
  double tmp = atan(b / a) * RAD;
  if (a == 0.0) return ((b < 0.0) ? -90.0 : 90.0); // Special case imaginary
  else if (a < 0.0) {
    return ((b < 0.0) ? (tmp - 180.0) : (tmp + 180.0)); // Quadrant 2 or quadrant 3
  }
  else return (tmp); // Quadrant 1 or 4
}

static boolean isreal(void) { // True if TOS is real
  return (dp ? ds[dp - 1].i == 0.0 : true);
}

static void prgstepins(byte c) { // Insert step (character c in prgbuf at prgeditstart)
  if (prgbuflen < PRGSIZEMAX) {
    for (byte i = prgbuflen; i > prgeditstart; i--) prgbuf[i] = prgbuf[i - 1];
    if (isprgeditfirst) prgbuf[prgeditstart] = c;
    else prgbuf[prgeditstart + 1] = c;
    prgbuflen++;
    prgeditstart++;
    fgm = 0;
  }
}

static void execute(byte command) { // Execute command
  if (command < MAXCMDB) (*dispatch[command])(); // Dispatch intrinsic/builtin command
  else if (command < MAXCMDU)
    mp = (seekusr(command) + PRGNAMEMAX) - EEUSTART + sizeof(mem); // Execute user command
  if (!isAF && command > 10 && command != 12) { // New number - except: 0-9.A-F CE
    decimals = 0; isdot = false; isnewnumber = true;
  }
  if (fgm && setfgm) fgm = setfgm = 0; // Hold demanded f-key status one cycle
  setfgm = 1;
}

static void floatstack() {
  memcpy(ds, &ds[1], (DATASTACKSIZE - 1) * sizeof(struct data));
  dp--;
  isfloated = true;
}

static void dpush(struct data c) { // Push complex number to data-stack
  if (dp >= DATASTACKSIZE) floatstack(); // Float stack
  ds[dp++] = c;
}
static double dpushr(double f) { // Push real number to data-stack
  dpush({f, NULL, NULL});
  return (f);
}
static void dpushb(int64_t n) { // Push business number to data-stack
  dpush({NULL, NULL, n});
}

static struct data dpop(void) { // Pop value from data-stack
  return (dp ? ds[--dp] : C0);
}
static float dpopr(void) { // Pop real number from data-stack
  return (dp ? ds[--dp].r : NULL);
}
static int64_t dpopb(void) { // Pop base number from data-stack
  return (dp ? ds[--dp].b : NULL);
}

static void apush(int addr) { // Push address (int) to address-stack
  if (ap >= ADDRSTACKSIZE) msgnr = MSGNEST; else as[ap++] = addr;
}
static int apop(void) { // Pop address (int) from address-stack
  return (ap ? as[--ap] : NULL);
}

static void B2stack (void) { // Copy business stack to stack
  for (byte i = 0; i < dp; i++)  ds[i].r = ds[i].b / 100.0;
}
static void stack2B (void) { // Copy stack to business stack
  for (byte i = 0; i < dp; i++)
    ds[i].b = (ds[i].r * 1000LL + 5LL) / 10LL; // Includes rounding
}

static int seekusr(byte n) { // Find run-address (ptr) of n-th function
  int ptr = EEUSTART;
  while (n - MAXCMDB) if (EEPROM[ptr++] == _END) n--;
  return (ptr);
}
static int seekusrp(int8_t n) { // Seekusr for prgselect+MAXCMDB + n
  return (seekusr(prgselect + MAXCMDB + n));
}
static void seekmem(byte n) { // Find run-address (mp) of n-th builtin function
  mp = 0;
  while (n + 1 - MAXCMDI) if (pgm_read_byte(mem + mp++) == _END) n--;
}

static void moveprgup(void) { // Move program in EEPROM up
  int a1 = seekusrp(-1), a2 = seekusrp(0), a3 = seekusrp(1);
  int a = a1 + a3 - a2;
  for (byte i = 0; i < a2 - a1; i++) prgbuf[i] = EEPROM[a1 + i]; // Rescue area1
  for (int i = a1; i < a; i++) EEPROM[i] = EEPROM[i + a2 - a1]; // Move EEPROM area
  for (byte i = 0; i < a2 - a1; i++) EEPROM[a1 + a3 - a2 + i] = prgbuf[i]; // Replace temp
  byte cmd1 = MAXCMDB + prgselect - 1, cmd2 = MAXCMDB + prgselect; // Changed programs
  for (byte n = 0; n < nou; n++) // Repair program calls in EEPROM
    for (int i = seekusr(n + MAXCMDB) + PRGNAMEMAX; i < seekusr(n + MAXCMDB + 1); i++)
      if (EEPROM[i] == cmd1) EEPROM[i] = cmd2;
      else if (EEPROM[i] == cmd2) EEPROM[i] = cmd1;
  for (int i = EEMENU; i < EEMENU + MENUITEMS; i++) // Repair program calls in user menu
    if (EEPROM[i] == cmd1) EEPROM[i] = cmd2;
    else if (EEPROM[i] == cmd2) EEPROM[i] = cmd1;
}

static void upn(byte n, byte l) { // Selection up l lines
  byte sel = select;
  if (select > n * l && select <= (n + 1) * l - 1) select--; else select = (n + 1) * l - 1;
}
static void downn(byte n, byte l) { // Selection down l lines
  if (select >= n * l && select < (n + 1) * l - 1) select++; else select = n * l;
}
static byte menuselect(byte lines) { // Selection (1 line = 16 items)
  char k = key;
  if (k == KEY1 || k >= KEY2 && k <= KEY4) { // Execute
    if (k == KEY1) {
      k = KEY8; // Cast f-key to key 6
      //delayshort(200); // To prevent early activation of the f-key
      key = oldkey;
    }
    return (select * 4 + k - '6');
  }
  else if (k == KEY5) upn(0, lines); // # Up0
  else if (k == KEY9) downn(0, lines); // # Down0
  else if (k == KEY6) upn(1, lines); // # Up1
  else if (k == KEY10) downn(1, lines); // # Down1
  else if (k == KEY7) upn(2, lines); // # Up2
  else if (k == KEY11) downn(2, lines); // # Down2
  else if (k == KEY8) upn(3, lines); // # Up3
  else if (k == KEY12) downn(3, lines); // # Down3
    else if (k == KEY14) if (select > 0) select--; else select = 4 * lines - 1; // # Left
    else if (k == KEY15) if (select < 4 * lines - 1) select++; else select = 0; // # Right
  else if (k == KEY13) return (NOPRINTNOKEY);
  return (PRINTNOKEY);
}

static void idofusr(void) { // Count size (sou) and number (nou) of user programs
  int ptr = EEUSTART;
  boolean loop = true;
  byte n = 0, tmp1 = EEPROM[ptr];
  if (tmp1 != _END || EEPROM[ptr + 1] != _END)
    while (loop) {
      byte tmp2 = EEPROM[++ptr];
      if (tmp1 == _END) {
        n++; if (tmp2 == _END) loop = false;
      }
      tmp1 = tmp2;
    }
  nou = n; sou = ptr + 1 - EEUSTART;
}

static void sort(void) { // Sort cmd[] alphabetically to cmdsort[]
  idofusr(); // Calculate nou first
  char s[2][4]; // Strings to compare
  for (byte i = 0; i < MAXCMDU; i++) cmdsort[i] = i; // Initialize
  for (byte k = MAXCMDB + nou - 1; k > 0; k--) { // Outer loop
    for (byte i = 0; i < k; i++) { // Inner loop
      for (byte m = 0; m < 2; m++) { // Catch 2 strings
        if (cmdsort[i + m] < MAXCMDB) // Intrinsic or builtin command
          strcpy_P(s[m], (char*)pgm_read_word(&(cmd[cmdsort[i + m]])));
        else { // User command
          int ptr = seekusr(cmdsort[i + m]);
          for (byte j = 0; j < 3; j++) s[m][j] = EEPROM[ptr++];
        }
      }
      if (strcmp(s[0], s[1]) > 0) { // Compare strings and swap commands
        byte tmp = cmdsort[i]; cmdsort[i] = cmdsort[i + 1]; cmdsort[i + 1] = tmp;
      }
    }
  }
}

static void printbuf(boolean shift, byte mh, byte y) { // Print sbuf[]
  byte dotx = 0;
  for (byte i = 0; i < DIGITS + 1; i++) {
    printcat(sbuf[i], FONT6, shift, SIZES, mh, INDICATOR + (FONTBIGWIDTH + 1) * i - dotx, y);
    if (sbuf[i] == '.') dotx = 4;
  }
}

static void printint(int n, boolean bitshift, byte x, byte y) { // Print integer number
  byte e = 1;
  int k = n; while (k /= 10) e++; // Number of digits
  sbuf[e] = NULL;
  do sbuf[--e] = _ones(n) + '0'; while (n /= 10); // Fill string
  printsat(sbuf, bitshift, SIZES, SIZES, x, y);
}

static double printsign(double f) { // Common code of printfix and printsci
  memset(sbuf, '/', sizeof(sbuf)); // Clear string buf ('/' = blank)
  if (f < 0.0) {
    f = - f;
    sbuf[0] = '-';
  }
  return (f);
}

static void printfix(double f, boolean bitshift, byte mh, byte y) { // Print float with fixed decimals
  long m; // Mantissa
  int8_t e = 1; // Exponent
  byte fix = 6;
  f = printsign(f);
  if (f >= 1.0) e = log10(f) + 1; // Calculate new exponent if (f !< 1)
  double d = (f * pow10(fix - e + 1) + 0.5) / pow10(fix - e + 1); // Rounding
  m = d;
  for (byte i = e; i > 0; i--) {
    sbuf[i] = _ones(m) + '0';
    m /= 10;
  }
  sbuf[e + 1] = '.';
  if ((long)f >= (long)d) d = f; // * Calculate after dot (and suppress trailing zeros)
  m = (d - (long)d) * pow10(fix - e + 1) + 0.5;
  boolean istrail = true;
  for (byte i = DIGITS; i > e + 1; i--) {
    byte one = _ones(m);
    if (isprintinput) { // Assign/suppress input line
      if (!istrail || (isnewnumber || i - e - 1 <= decimals) && (!isnewnumber || one != 0)) {
        sbuf[i] = one + '0'; // Assign digit
        istrail = false; // End of trailing zeros
      }
    }
    else if (!istrail || one != 0) { // Suppress digit in non input line
      sbuf[i] = one + '0'; // Assign digit
      istrail = false; // End of trailing zeros
    }
    m /= 10L;
  }
  printbuf(bitshift, mh, y);
}

static void printsci(double f, boolean bitshift, byte mh, byte y) { // Print float with mantissa height (mh) at line y
  long m; // Mantissa
  int8_t e; // Exponent
  f = printsign(f);
  e = log10(f); // Exponent
  m = (f / pow10(e - FIXSCI)) + 0.5; // Mantissa
  if (m > 0 && m < pow10(FIXMANT)) m = (f / pow10(--e - FIXSCI)) + 0.5; // "New" mantissa
  for (byte i = (FIXSCI + 2); i > 0; i--) { // Print mantissa
    if (i == 2) sbuf[i] = '.';
    else {
      sbuf[i] = _ones(m) + '0';
      m /= 10;
    }
  }
  if (e < 0) { // Negative exponent
    sbuf[6] = '-';
    e = -e;
  }
  sbuf[7] = (e >= 10) ? _tens(e) + '0' : '0'; // Exponent
  sbuf[8] = _ones(e) + '0';
  printbuf(bitshift, mh, y);
}

static void printbase() { // Print TOS for base (10 or other)
  printcat(dp ? dp - 1 + 'a' : 'B', FONT4, false, SIZES, SIZES, 0, 0); // Base indicator
  printint(base, false, (base < 10) ? 60 : 55, 0); // Print base
  int64_t n = NULL;
  if (dp) n = ds[dp - 1].b;
  if (base != 10) n /= 100;
  byte space = 0;
  boolean sign = false;
  if (n < NULL) { // Handle sign
    n = -n;
    sign = true;
  }
  for (byte i = BDIGITS; i > 0; i--) { // Number to string
    byte c = n % base + '0';
    if (c > '9') c += 'A' - '9' - 1;
    sbuf[i - 1] = c;
    n /= base;
  }
  byte trnc = 0, left = (base == 10) ? 3 : 1;
  while (sbuf[trnc] == '0' && trnc < BDIGITS - left) sbuf[trnc++] = ' '; // Truncate zeros
  if (sign) sbuf[trnc - 1] = '-'; // Sign
  if (dp) { // Do not print empty stack
    byte start = 0;
    if (base != 10) start = 4;
    byte siz, y, pos, x;
    for (byte i = start; i < BDIGITS; i++) {
      if (base == 10) { // Printing parameters for base=10
        siz = i > BDIGITS - 3 ? SIZES : SIZEM;
        y = (i < 9) ? 0 : (siz == SIZEM) ? 2 : 3;
        pos = y ? (i - 9) * 5 - 3 : i * 5;
        if (i % 3 == 0) space += 2;
        x = 5 + pos + space - (y ? 5 : 2) - (siz == SIZES ? 1 : 0);
      }
      else { // Printing parameters for base!=10
        siz = SIZEM;
        y = (i < 12) ? 0 : 2;
        pos = y ? (i - 12) * 5 : (i - 3) * 5 + 1;
        if (i % 4 == 0) space += 3;
        x = pos + space;
      }
      printcat(sbuf[i], FONT4, true, SIZES, siz, x, y); // Print
    }
  }
}

static void printnum(double f, boolean bitshift, byte mh, byte y, byte ind) { // Print number
  double a = _abs(f);
  if (dp)
    if (a < ALMOSTZERO || a >= FIXMIN && a < FIXMAX) printfix(f, bitshift, mh, y); // Fixed format
    else printsci(f, bitshift, mh, y); // Sci format
  printcat(ind, FONT4, false, SIZES, SIZES, 0, y); // Indicator
}

static void printxy() { // Print X and Y (real/imaginary, big/small)
  double a, b;
  if (dp) a = ds[dp - 1].r; else a = 0.0;
  if (dp > 1) b = ds[dp - 2].r; else b = 0.0;
  byte ca = dp ? 'a' + dp - 1 : '}', cb = (dp > 1) ? 'a' + dp - 2 : '-';
  byte lina = 2;
  byte siz = SIZEM;
  if (!isreal())
    if (ispolar) { // ABS PHI
      a = absolute(ds[dp - 1].r, ds[dp - 1].i);
      b = angle(ds[dp - 1].r, ds[dp - 1].i);
      cb = '`';
    }
    else { // RE IM
      a = ds[dp - 1].r; b = ds[dp - 1].i;
      cb = 'i';
    }
  if (isdict || ismenu || isprgrename/*|| isprintalpha /* || isslot*/) { // Small, lines 0 and 1
    siz = SIZES; lina = 1;
  }
  isprintinput = true; printnum(a, false, siz, lina, ca); isprintinput = false; // a
  if ((!isreal() || dp > 1) && !isprintalpha) printnum(b, false, siz, 0, cb); // b
}

static void makesbuf(int8_t tmp) { // Common code to prepare sbuf
  for (byte i = 0; i < PRGNAMEMAX; i++) sbuf[i] = EEPROM[prgaddr + i];
  sbuf[PRGNAMEMAX] = NULL;
}
static void printfkeys(byte i) { // Common code to print sbuf
  printsat(sbuf, true, SIZES, SIZES, i * 16 + i / 2, 3);
}

static void printmsg(byte nr) { // Print message
  strcpy_P(sbuf, (char*)pgm_read_word(msg + nr));
  printsat(sbuf, true, SIZES, SIZES, 0, 2);
  msgnr = 0;
}

static void printindicator(byte sign) {
  printcat(sign, FONT4, true, SIZES, SIZES, 0, 3); // f/g
}

static boolean printseledit(int addr) { // Similar code of printing prg select and edit
  for (byte i = 0; i < PRGNAMEMAX; i++) sbuf[i] = EEPROM[addr + i];
  sbuf[PRGNAMEMAX] = NULL;
}

static void fillsbuf(int addr) { // Fill sbuf with cmd
  strcat_P(sbuf, (char*)pgm_read_word(cmd + addr));
}

static boolean printscreen(void) { // Print screen
  dbuffill(NULL);
  if (fgm) printindicator((fgm == ISF) ? '[' : ']'); // f/g
  if (!isnewnumber && !darkscreen) printindicator('_'); // Indicate number input
  if (isfloated) { // Indicate stack flow (data loss)
    printindicator('!');
    isfloated = false;
  }
  if (!darkscreen && !base && (isdict || ismenu || isprgrename)) // Print select
    printint(select + 1, false, (select + 1 <= 9) ? 60 : 55, 2);
  if (istorch) dbuffill(0xff);
  else if (darkscreen) {}
  else if (isgetkey) printmsg(MSGASK);
  else if (msgnr) printmsg(msgnr);
  else if (base) printbase(); // Print base mode
  else if (issolve || isint || isplotcalc) printmsg(MSGRUN); // # Print "run" message
  else if (isdict || ismenu) { // # Dict and Menu
    printmsg(isdict ? MSGDICT : ismenusetusr ? MSGKEY : MSGMENU);
    for (byte i = 0; i < 4; i++) {
      byte tmp = select * 4 + i;
      if (ismenu) tmp = EEPROM[EEMENU + tmp];
      else tmp = cmdsort[tmp];
      sbuf[0] = NULL;
      if (tmp < MAXCMDB) fillsbuf(tmp); // Intrinsic or builtin command
      else if (tmp < MAXCMDB + nou) { // User command
        int ptr = seekusr(tmp);
        for (byte i = 0; i < 3; i++) sbuf[i] = EEPROM[ptr++];
        sbuf[3] = NULL;
      }
      else {
        sbuf[0] = ' '; sbuf[1] = '_'; sbuf[2] = NULL;
      }
      printfkeys(i);
    }
    printxy();
  }
  else if (isprgselect) { // # Select program
    byte nr = prgselect;
    for (byte i = 0; i < MAXLIN; i++) {
      if (nr + i < nou) {
        printint(nr + i + 1, false, 8, i); // Print size of prg
        sbuf[0] = NULL;
        int addr = seekusr(MAXCMDB + prgselect + i);
        printseledit(addr);
        printsat(sbuf, false, SIZES, SIZES, 22, i);
      }
    }
    printcat('}', FONT4, false, SIZES, SIZES, 0, 0); // Cursor
    printint(nou, false, 50, 0); // Print nou
    printint(sou, false, 50, 2); // Print sou
    printint(EEU - sou, false, 50, 3); // Print free space
  }
  else if (isprgrename) { // # Rename program
    makesbuf(prgselect);
    printsat(sbuf, true, SIZES, SIZES, 0, 2);
    for (byte i = 0; i < 4; i++) {
      sbuf[0] = select * 4 + FONTOFFSET + i; sbuf[1] = NULL;
      printfkeys(i);
    }
    printxy();
  }
  else if (isprgedit) { // # Edit program
    printint(prgbuflen, false, 55, 0); // Print size of prg
    for (byte i = 0; i < MAXLIN; i++) {
      byte pi = prgeditstart + i;
      byte cmdpi = prgbuf[pi];
      if (pi < prgbuflen) {
        printint(pi + 1, false, 8, i); // Print size of prg
        sbuf[0] = NULL;
        if (cmdpi < MAXCMDB) fillsbuf(cmdpi);
        else {
          int addr = seekusr(cmdpi);
          printseledit(addr);
        }
        printsat(sbuf, false, SIZES, SIZES, 22, i);
      }
      printcat('{', FONT4, false, SIZES, SIZES, 0, 0);
    }
  }
  else if (isplot) { // Plot
    double ymax = plot[0], ymin = plot[0];
    for (byte i = 0; i < SCREENWIDTH; i++) { // Find ymax and ymin
      ymax = max(ymax, plot[i]); ymin = min(ymin, plot[i]);
    }
    double yscale = (ymax - ymin) / SCREENHEIGHT;
    if (plota * plotb <= 0) printvline(-plota * (SCREENWIDTH / (plotb - plota))); // Y-axis
    if (ymin * ymax <= 0) printhline(SCREENHEIGHT + ymin / yscale); // X-axis
    for (byte i = 0; i < SCREENWIDTH; i++) // Function plot
      printpixel(i, SCREENHEIGHT + (ymin - plot[i]) / yscale);
  }
  else printxy();
  if (isprintalpha) printsat(alpha, false, SIZES, SIZES, 0, 0); // Print alpha anyway
  display();
  return (NULL); // To determine isprintscreen
}


// SETUP, LOOP
void setup() {
  // Do some stuff while warming up the display
  sort(); // Count sou and nou - Sort commands alphabetically
  darktime = EEPROM[EEDARKTIME]; limitdarktime(); // Load darktime
  base = EEPROM[EEBASE]; // Load business mode flag

  //delaylong(6);
  delaylong(4);
  bootpins(); // System boot procedure
  bootSPI();
  bootscreen();
  setframerate(FRAMERATE);
}


void loop() {

  if (isprintscreen) isprintscreen = printscreen(); // Print screen
  if (pause) { // Pause
    delaylong(pause);
    pause = 0;
  }

  if (mp) { // *** Execute/run code
    if (mp < sizeof(mem)) key = pgm_read_byte(mem + mp++); // Builtin
    else if (mp < sizeof(mem) + sou) key = EEPROM[mp++ -sizeof(mem) + EEUSTART]; // User
    else mp = 0; // cmd > MAXCMDU
    if (key >= MAXCMDI && key != _END) apush(mp); // Subroutine detected - branch
    if (key == _END) { // _END reached
      if (ap) mp = apop(); // End of subroutine - return
      else { // End of run
        mp = 0;
        isprintscreen = true; // Finally print screen
      }
    }
    else execute(key);
    digitalWrite(KEYBOARDCOL1, LOW); // Stop by pressing C
    if (!digitalRead(KEYBOARDROW4)) mp = ap = 0;
    digitalWrite(KEYBOARDCOL1, HIGH);
  }

  else { // *** Evaluate valid new key
    if (!(nextFrame())) return; // Idle for next frame
    key = getkey(); // READ KEY

    if (key == KEY13) issolve = isint =  isplot = istorch = false; // Stop execution
    if (key == KEY1 && !base) { // Check MENU (longpressed f)
      if (millis() - timestamp > FLONGPRESSTIME) {
        if (isprgedit) { // Menu from prgedit demanded
          isprgmenu = true; isprgedit = false;
        }
        else { // Menu demanded
          fgm = 0;
          freleased = false;
        }
        ismenu = isprintscreen = true;
        select = 0; // Comment out, if menu should't start at 0
      }
    }
    else timestamp = millis();

    if (millis() - powertimestamp > darktime * 10000L) { // Dark if no activity
      _keygoff();
      isprintscreen = true;
    }

    if (issolve) { // # SOLVE
      cycles++;
      if (cycles < 3) { // First run - f(x0)
        execute(MAXCMDB);
        if (cycles == 2) { // Second run - f(x0+dx)
          f0 = dpopr(); // Save f0 from first run
          dpushr(x0 + DELTAX); // Prepare new x-value for next run
        }
      }
      else { // Third run - x1
        double diffx = DELTAX / (dpopr() / f0 - 1.0);
        dpushr(x0 -= diffx); // Improved x-value
        cycles = 0;
        if (diffx < DELTAX && diffx > -DELTAX) { // Exit
          isnewnumber = true; issolve = false;
          isprintscreen = true;
        }
      }
    }
    else if (isint) { // # INTEGRATE
      cycles++;
      execute(MAXCMDB);
      if (cycles == 1) {} // First run - f(b)
      else if (cycles == 2) { // Second run - f(a)
        intf += dpopr(); // F=F+f(b)
        dpushr(inta);
      }
      else if (cycles == 3) { // Third run - xa
        intf += dpopr(); // F=F+f(a)
        dpushr(intx = inta + intdelta);
      }
      else if (cycles <= 2 * INTSTRIPES - 1 + 3) { // 2n-1 stripes
        double tmp = 4 * ((cycles - 3) / 2.0 - (int)((cycles - 3) / 2.0) + 0.5);
        tmp *= dpopr(); intf += tmp;
        dpushr(intx += intdelta);
      }
      else { // Last run
        dpopr(); // Delete last push (intx)
        dpushr(intf * intdelta / 3);
        mp = 0; // Prevent one more cycle
        isnewnumber = true; isint = false; // Exit
        isprintscreen = true;
      }
    }
    if (isplotcalc) { // # PLOT
      execute(MAXCMDB); // Execute first user program
      if (cycles == 0) {} // First run
      else if (cycles <= SCREENWIDTH) { // SCREENWIDTH runs
        plot[cycles - 1] = dpopr();
        dpushr(plota + cycles * plotd);
      }
      else isplotcalc = false;
      cycles++;
    }

    if (key != oldkey) {
      oldkey = key; // New valid key is old key
      freleased = true;
      if (key < NOPRINTNOKEY) {
        powertimestamp = millis(); // Keep awake when active
        darkscreen = false; // Reactivate screen in case of dark

        if (isgetkey) { // ### Get keypress
          byte k;
          while ((k = getkey()) >= NOPRINTNOKEY) ; // Wait for keypress
          dpushr(k - '0');
          isgetkey = false;
        }

        else if (isdict) { // ### Dictionary
          byte tmp = menuselect(MAXCMDU / 16);
          if (tmp < PRINTNOKEY) { // Item selected
            if (issetusr) { // Go back to select menu slot
              //setusrselect = tmp;
              setusrselect = cmdsort[tmp];
              select = 0;
              issetusr = false; ismenu = ismenusetusr = true;
            }
            else if (isprgdict) { // Go back to prgedit
              prgstepins(tmp);
              isprgdict = false; isprgedit = true;
            }
            else { // Execute command directly
              execute(cmdsort[tmp]); // Execute dict choice
              isnewnumber = true;
            }
            isdict = false;
          }
          else if (tmp == NOPRINTNOKEY) { // Escape
            key = NOPRINTNOKEY;
            isdict = false;
          }
        }

        else if (ismenu) { // ### Menu
          if (freleased) { // Execute only if f-key was released
            byte tmp = menuselect(2);
            if (tmp < PRINTNOKEY) { // Item selected
              if (ismenusetusr) { // Save user menu entry
                EEPROM[EEMENU + tmp] = setusrselect;
                ismenusetusr = false;
              }
              else if (isprgmenu) { // Go back to prgedit
                prgstepins(EEPROM[EEMENU + tmp]);
                isprgmenu = false; isprgedit = true;
              }
              else { // Execute selected command
                execute(EEPROM[EEMENU + tmp]); // Execute directly
                isnewnumber = true;
              }
              ismenu = false;
            }
            else if (tmp == NOPRINTNOKEY) ismenu = ismenusetusr = false; // Escape
          }
        }

        else if (isprgselect) { // ### Select program
          if (key == KEY5) // # 6 - move up
            if (prgselect > 0) prgselect--;
            else prgselect = nou - 1;
          else if (key == KEY9) // # 3 - move down
            if (prgselect < nou - 1) prgselect++;
            else prgselect = 0;
          else if (key == KEY14) { // # 0 - rename program
            prgaddr = seekusrp(0);
            select = renamenr = 0;
            isprgrename = true; isprgselect = false;
          }
          else if (key == KEY10) { // # 1 - new program
            prgeditstart = prgbuflen = 0;
            isprgnew = isprgeditfirst = isprgedit = true; isprgselect = false;
            sort();
          }
          else if (key == KEY15) { // # Dot - delete program
            if (nou > 1) {
              int a1 = seekusrp(0), a2 = seekusrp(1);
              byte diff = a2 - a1;
              for (int i = a1; i < EEUSTART + sou - diff; i++) // Adjust programs
                EEPROM[i] = EEPROM[i + diff];
              if (prgselect == nou - 1) prgselect--; // Last program in list deleted
            }
            else { // Delete the last remaining program -> format
              EEPROM[EEUSTART] = _END; EEPROM[EEUSTART + 1] = _END;
              prgselect = 0;
            }
            sort();
          }
          else if (key == KEY8) { // # 6 - move up
            if (prgselect) {
              moveprgup(); prgselect--;
            }
          }
          else if (key == KEY12) { // # 3 - move down (= move up with prgselect++)
            if (prgselect < nou - 1) {
              prgselect++;
              moveprgup();
            }
          }
          else if (key == KEY11) { // # 2 - load program (in)
            byte in, nr = 0;
            long tim = millis();
            prgbuf[0] = NULL;
            while (Serial.available() > 0) byte tmp = Serial.read(); // Flush serial buffer
            while (Serial.available() <= 0 && millis() - tim < 3000) ; // Wait for serial input
            while (Serial.available() > 0 && (in = Serial.read()) >= ' ' && nr < PRGSIZEMAX) {
              prgbuf[nr++] = in - ' ';
              prgbuf[nr] = _END;
              sort();
            }
            prgbuflen = nr;
            isprgnew = isprgedit = true; isprgselect = false;
          }
          else if (key == KEY7) { // # 5 - save program (out)
            for (int i = seekusrp(0) + 3; i < seekusrp(1) - 1; i++)
              Serial.write(EEPROM[i] + ' ');
            delayshort(200);
          }
          else if (key == KEY16 && nou) { // # Enter - edit program
            prgaddr = seekusrp(0);
            prgbuflen = seekusrp(1) - prgaddr - PRGNAMEMAX - 1;
            oldprgbuflen = prgbuflen; // Save length for later
            for (byte i = 0 ; i < prgbuflen; i++) prgbuf[i] = EEPROM[prgaddr + PRGNAMEMAX + i];
            prgbuf[prgbuflen] = NULL;
            isprgselect = false; isprgedit = true;
          }
          else if (key == KEY13) isprgselect = false; // # Escape
        }

        else if (isprgrename) { // ### Program rename
          byte tmp = menuselect(6);
          if (tmp < PRINTNOKEY) // Item selected - replace letter of program name
            EEPROM[prgaddr + renamenr++] = tmp + ' ';
          if (tmp == NOPRINTNOKEY || renamenr >= PRGNAMEMAX) { // Escape
            isprgrename = false; isprgselect = true;
          }
          sort();
        }

        else if (isprgedit) { // ### Program edit
          if (key == KEY1) { // # F-key
            if (fgm == ISG) fgm = 0; else if (fgm == ISF) fgm = ISG; else fgm = ISF;
          }
          else if (key == KEY6 && fgm == ISF) { // # F-4 ... select via dict
            select = 0; fgm = 0; isprgdict = isdict = true; isprgedit = false;
          }
          else if (fgm == ISF || fgm == ISG) // # Insert F- or G-shifted key
            prgstepins(key - '0' + fgm * 16);
          else if (key == KEY5) // # Up
          {
            if (prgeditstart > 0) prgeditstart--; else prgeditstart = prgbuflen - 1;
            isprgeditfirst = false;
          }
          else if (key == KEY9) // # Down
          {
            if (prgeditstart < prgbuflen - 1) prgeditstart++; else prgeditstart = 0;
            isprgeditfirst = false;
          }
          else if (key == KEY15) { // # Dot - Delete step
            if (prgbuflen) {
              for (byte i = prgeditstart; i < prgbuflen; i++) prgbuf[i] = prgbuf[i + 1];
              prgbuflen--;
              if (prgeditstart == prgbuflen && prgeditstart) prgeditstart--; // Deleted last step
              if (isprgeditfirst && prgeditstart) prgeditstart--;
              if (!prgeditstart) isprgeditfirst = true;
            }
          }
          else if (key <= KEY4 || key == KEY16) prgstepins(key - '0'); // # Insert direct key
          else if (key == KEY13) { // # Escape and save program to EEPROM
            if (isprgnew) { // Save new program
              if (sou + prgbuflen >= EEU) msgnr = MSGSAVE; // New program is to big
              else {
                for (byte i = 0; i < PRGNAMEMAX; i++) EEPROM[EEUSTART + sou - 1 + i] = '-';
                for (byte i = 0; i < prgbuflen; i++) // Save program to EEPROM
                  EEPROM[EEUSTART + sou + PRGNAMEMAX - 1 + i] = prgbuf[i];
                for (byte i = 0; i < 2; i++) // Add 2 x _END
                  EEPROM[EEUSTART + sou + PRGNAMEMAX - 1 + prgbuflen + i] = _END;
                sort();
              }
              isprgnew = false;
            }
            else { // Save edited program
              int8_t diff = prgbuflen - oldprgbuflen;
              if (diff < 0) // New program is smaller
                for (int i = prgaddr + PRGNAMEMAX; i <= EEUSTART + sou; i++) // Adjust programs
                  EEPROM[i] = EEPROM[i - diff];
              else if (diff > 0) // New program is bigger
                for (int i = EEUSTART + sou + diff; i >= prgaddr + PRGNAMEMAX; i--) // Adjust programs
                  EEPROM[i] = EEPROM[i - diff];
              for (byte i = 0; i < prgbuflen; i++) // Save program to EEPROM
                EEPROM[prgaddr + PRGNAMEMAX + i] = prgbuf[i];
              sort();
            }
            prgbuflen = prgeditstart = 0; isprgselect = true; isprgedit = false;
          }
        }

        else execute(key - '0' + fgm * 16); // ### Execute key
        isprintscreen = true;
      }
    }
  } // End of evaluating key

}
