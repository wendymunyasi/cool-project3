/*  BFile.CC
   ----------------------------------------------------------------
   Jim Sare - jimsare@ameritech.net
   Last Modified: 04/17/1998

   Binary File read/write routines. This is a subclass
   of the file class in Visual dBASE 7 .
     
   ReadDouble, WriteDouble, ReadLDouble, WriteLDouble are based on
   code by Ken Chan and rewritten to support direct file read/write.
  
   NOTE: There is no error checking to ensure that values passed
         to the Write functions are within the proper range.
  
         There is no EOF handling within this class. EOF handling
         should be performed prior to and/or after Read calls.
  
         Backup any files that will be accessed via this class.
  
   Usage:
      Write To File:
          b = New BFile()		// Create a new instance
          b.Create("Test.BIN")	// Create a file/overwrite existing
          b.WriteULong(0xAA55AA55) 	// Write unsigned long
          b.WriteUShort(0x55AA)		// Write unsigned short
          b.Close()			// Close the file
      Read From File:
          b = New BFile()		// Create a new instance
          b.Open("Test.BIN")		// Open existing binary file
          ? IToH(b.ReadULong())		// Read unsigned long
          ? IToH(b.ReadUShort())	// Read unsigned short
          b.Close()			// Close the file

   Methods:

        ReadChar()
           Read 8-bit signed numeric
        ReadDouble()
           Read 64-bit float
        ReadLDouble()
           Read 80-bit float
        ReadLong()
           Read 32-bit signed numeric
        ReadShort()
           Read 16-bit signed numeric
        ReadUChar()
           Read 8-bit unsigned numeric
        ReadULong()
           Read 32-bit unsigned numeric
        ReadUShort()
           Read 16-bit unsigned numeric
        WriteChar()
           Write 8-bit signed numeric
        WriteDouble()
           Write 64-bit float
        WriteLDouble()
           Write 80-bit float
        WriteLong()
           Write 16-bit signed numeric
        WriteShort()
           Write 16-bit signed numeric
        WriteUChar()
           Write 8-bit unsigned numeric
        WriteULong()
           Write 32-bit unsigned numeric
        WriteUShort()
           Write 16-bit unsigned numeric
   ----------------------------------------------------------------
*/

CLASS BFile Of File

	// Type		Description		Size		Range
	// -----------------------------------------
	// UChar		unsigned char 	8 bits	0 to 255
	// Char		char				8 bits	-128 to 127
	// UShort	ushort			16 bits	0 - 65535
	// Short		short int		16 bits	-32,768 to 32,767
	// ULong		unsigned long	32 bits	0 to 4,294,967,295
	// Long		long				32 bits	-2,147,483,648 to 2,147,483,647
	// Double	double			64 bits	1.7 x 10-308 to 1.7 x 10+308
	// LDouble	long double		80 bits	3.4 x 10-4932 to 1.1 x 10+4932

	#define DOUBLE_EBIAS			0x3FF
	#define DOUBLE_MANTBITS		52
	#define LDOUBLE_EBIAS		0x3FFF
	#define LDOUBLE_MANTBITS	64

	FUNCTION ReadUChar			// Read 8-bit unsigned numeric

		RETURN Asc(this.Read(1))

	FUNCTION WriteUChar(n)		// Write 8-bit unsigned numeric

		RETURN this.Write(Chr(BitAnd(n, 0xFF)))

	FUNCTION ReadChar				// Read 8-bit signed numeric
		LOCAL n

		n = this.ReadUChar()
		RETURN IIf(n < 0x80, n, -0x100 + n)

	FUNCTION WriteChar(n)		// Write 8-bit signed numeric

		RETURN this.WriteUChar(IIf(n > 0, BitAnd(n, 0x7F), 0x100 + n))

	FUNCTION ReadUShort			// Read 16-bit unsigned numeric
		LOCAL c

		c = this.Read(2)
		RETURN Int(Asc(SubStr(c, 1)) +;
						BitLShift(Asc(SubStr(c, 2)), 8))

	FUNCTION WriteUShort(n)		// Write 16-bit unsigned numeric

		RETURN this.Write(Chr(BitAnd(n, 0xFF)) +;
								Chr(BitAnd(BitRShift(n,  8), 0xFF)))

	FUNCTION ReadShort			// Read 16-bit signed numeric
		LOCAL n

		n = this.ReadUShort()
		RETURN IIf(n < 0x8000, n, -0x10000 + n)

	FUNCTION WriteShort(n)		// Write 16-bit signed numeric

		RETURN this.WriteUShort(IIf(n > 0, n, 0x10000 + n))

	FUNCTION ReadULong			// Read 32-bit unsigned numeric
		LOCAL c

		c = this.Read(4)
		RETURN Int(Asc(SubStr(c, 1)) +;
					BitLShift(Asc(SubStr(c, 2)),  8) +;
					BitLShift(Asc(SubStr(c, 3)), 16) +;
					BitLShift(Asc(SubStr(c, 4)), 24))

	FUNCTION WriteULong(n)		// Write 32-bit unsigned numeric

		RETURN this.Write(Chr(BitAnd(n, 0xFF)) +;
								Chr(BitAnd(BitRShift(n,  8), 0xFF)) +;
								Chr(BitAnd(BitRShift(n, 16), 0xFF)) +;
								Chr(BitAnd(BitRShift(n, 24), 0xFF)))

	FUNCTION ReadLong				// Read 32-bit signed numeric
		LOCAL n

		n = this.ReadULong()
		RETURN IIf(n < 0x80000000, n, -0x100000000 + n)

	FUNCTION WriteLong(n)		// Write 32-bit signed numeric

		RETURN this.WriteULong(IIf(n > 0, n, 0x100000000 + n))

	FUNCTION ReadDouble			// Read 64-bit float
		LOCAL c, n, bNeg, nExp, nMant

		c = this.Read(8)
		n = Asc(SubStr(c, 8))
		bNeg = BitSet(n, 7)
		nExp = BitLShift(BitAnd(n, 0x7F), 4)
		n = Asc(SubStr(c, 7))
		nExp += BitZRShift(n, 4)
		nMant = 0x10 + BitAnd(n, 0x0F)
		For n = 6 To 1 Step -1
			nMant *= 256.0
			nMant += Asc(SubStr(c, n))
		EndFor
		nMant *= 2^(nExp - DOUBLE_EBIAS - DOUBLE_MANTBITS)
		RETURN IIf(bNeg, -nMant, nMant)

	FUNCTION WriteDouble(n)		// Write 64-bit float
		LOCAL nAbs, bNeg, nExp, nMant, nInd, c

		c = ""
		bNeg = n < 0
		nAbs = Abs(n)
		nExp = Floor(Log(nAbs) / Log(2))
		nMant = Floor(nAbs / 2^(nExp - DOUBLE_MANTBITS))
		nExp += DOUBLE_EBIAS
		For nInd = 1 To 6
			c += Chr(nMant % 0x100)
			nMant /= 0x100
		EndFor
		nMant := BitAnd(nMant, 0x0F)
		c += Chr(nMant + BitLShift(BitAnd(nExp, 0x0F), 4))
		nExp := BitZRShift(nExp, 4)
		c += Chr(nExp + IIf(bNeg, 0x80, 0))
		RETURN this.Write(c)

	FUNCTION ReadLDouble			// Read 80-bit float
		LOCAL c, n, bNeg, nExp, nMant

		c = this.Read(10)
		n = Asc(SubStr(c, 9)) + BitLShift(Asc(SubStr(c, 10)), 8)
		bNeg = BitSet(n, 15)
		nExp = BitAnd(n, 0x7FFF)
		nMant = 0
		For n = 8 To 1 Step -1
			nMant *= 256.0
			nMant += Asc(SubStr(c, n))
		EndFor
		nMant *= 2^(nExp - LDOUBLE_EBIAS - LDOUBLE_MANTBITS + 1)
		RETURN IIf(bNeg, -nMant, nMant)

	FUNCTION WriteLDouble(n)	// Write 80-bit float
		LOCAL nAbs, bNeg, nExp, nMant, nInd, c

		c = ""
		bNeg = n < 0
		nAbs = Abs(n)
		nExp = Floor(Log(nAbs) / Log(2))
		nMant = Floor(nAbs / 2^(nExp - LDOUBLE_MANTBITS + 1))
		nExp += LDOUBLE_EBIAS
		For nInd = 1 To 8
			c += Chr(nMant % 0x100)
			nMant /= 0x100
		EndFor
		c += Chr(BitAnd(nExp, 0xFF))
		nExp := BitZRShift(nExp, 8)
		c += Chr(nExp + IIf(bNeg, 0x80, 0))
		RETURN this.Write(c)

ENDCLASS  // BFile Of File

// EOF: BFile.CC
