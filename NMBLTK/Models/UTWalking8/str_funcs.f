c  This file contains 7 sub programs:

c   1. strcrnch - remove spaces from a string and then left justify it.
c   2. strlen  - find the last non-space character in a string.
c   3. strtime - put the time into a string character in the hh:mm:ss format.
c   4. strscan - search for all occurences of a single character in a string.
c   5. lcase - force all characters of a string to be lower case.
c   6. ucase - force all characters of a string to be upper case.
c   7. strnums - write two numbers to a file, separated by a tab, and
c                containing no blank spaces.

c==============================================================================
c  Revision record:
c   10/1/93  11:15 am
c==============================================================================



      subroutine strcrnch(string,ilen)

c  This subroutine crunches a character string by removing any spaces and then 
c   left justifying it.

      implicit none

      integer i,iltr,ilen,csize

      character*1 space
      character*(*) string

      data space/' '/

      csize = len(string)


      iltr=1
      do 5 i=1,csize

      if(string(i:i) .ne.space)then
       string(iltr:iltr)=string(i:i)
       iltr=iltr+1
      endif

5     continue

      do 15 i=iltr,csize
       string(i:i)=space
15    continue

      ilen=iltr-1

      return
      end



      integer function strlen(string)

c  This function finds the last non-space character in a string.

      implicit none

      integer i,j
      character*1 space
      character*(*) string

      data space/' '/

      j = len(string)
      strlen = 0

      do 5 i = j,1,-1

       if(string(i:i) .ne. space)then
        strlen = i
        return
       endif

5     continue

      return
      end



      subroutine strtime(stm,strtm)

c  This subroutine puts the value of "stm" in seconds into the character
c   string "strtm" in the hour:minute:second format.

c   Note: strtm must be at least 7 bytes long.


      implicit none

      integer i,se,sb,me,mb
      integer istm,imtm,ihtm,num
      real stm,mtm,htm,temp
      character*4 frmt(5)
      character*(*) strtm

      data frmt/'(i1)','(i2)','(i3)','(i4)','(i5)'/


c  Get the length of "strtm". This will determine where the hours, minutes, 
c   and seconds will be placed in the string:
      se = len(strtm)

c  Clear the string:
      do i = 1,se
       strtm(i:i) = ' '
      enddo

      if(se .lt. 7)return

      sb = se-1
      me = sb-2
      mb = me-1

      i = me+1
      strtm(i:i) = ':'

      i = mb-1
      strtm(i:i) = ':'



c  Determine the number of hours, minutes, and seconds.
      htm=float(int(stm/3600.0))
      temp=stm-htm*3600.0
      mtm=float(int(temp/60.0))
      istm=int(temp-mtm*60.0)
      ihtm=int(htm)
      imtm=int(mtm)


c  Determine the format for the hours:
      if(htm .gt. 0.0)then
       i = max0( 0 , int(alog10(htm)) ) + 1
      else
       i = 1
      endif


c  Push the hours into "strtm":
      write(strtm(1:i),frmt(i))ihtm


c  Push the minutes into "strtm":
      write(strtm(mb:me),'(i2.2)')imtm


c  Push the seconds into "strtm":
      write(strtm(sb:se),'(i2.2)')istm


c  Crunch the string to the left:
      call strcrnch(strtm,i)


      return
      end




      integer function strscan(string,letter,occurs)

c  This function scans "string" and searches for all occurences of "letter".
c   The position of each occurence are given in "occurs". The total number of
c   occurences is given by the value of "strscan".

c   Note: the length of the vector "occurs" must be at least that of "string".


      implicit none

      integer i,slen,occurs(*)

      character*1 letter
      character*(*) string


      strscan = 0
      slen = len(string)


      do 5 i = 1,slen

       if(string(i:i) .eq. letter)then
        strscan = strscan + 1
        occurs(strscan) = i
       endif

5     continue


      return
      end




      subroutine lcase(string)

c  This subroutine forces all the characters of a string to be lower case.

      implicit none

      integer i,strlen,ascnum
      character*(*) string


      strlen = len(string)

      do 5 i = 1,strlen

       ascnum = ichar(string(i:i))

       if((ascnum .gt. 64) .and. (ascnum .lt. 91))then
        string(i:i) = char(ascnum+32)
       endif

5     continue

      return
      end




      subroutine ucase(string)

c  This subroutine forces all the characters of a string to be upper case.

      implicit none

      integer i,strlen,ascnum
      character*(*) string


      strlen = len(string)

      do 5 i = 1,strlen

       ascnum = ichar(string(i:i))

       if((ascnum .gt. 96) .and. (ascnum .lt. 123))then
        string(i:i) = char(ascnum-32)
       endif

5     continue

      return
      end






      integer function strnums(i1,i2,r1,r2,d1,d2,which,fnum,form1,form2)

c  This subroutine writes two numbers to a specified file. The numbers are
c   converted to character strings, the second is concatenated onto the first
c   (separated by a tab), and then all the blank spaces are removed.
c   The resulting string is written to the file.
c  
c______________________________________________________________________________
c
c  Input:
c   i1 = first integer value
c   i2 = second integer value
c   r1 = first single precision value
c   r2 = second single precision value
c   d1 = first double precision value
c   d2 = second double precision value
c
c   which = a vector of length 2 or more indicating which of the preceding
c            arguments are to be written to the file.
c
c    fnum = number of the file to which the numbers will be written.
c
c   form1 = a character string specifying the complete format for how the first
c            argument must be converted.
c   form2 = a character string specifying the complete format for how the
c            second argument must be converted.
c
c    Note: form1 and form2 must be completely valid format specifications.
c          The maximum size of the format specification is 20 characters.
c          Examples -> (f10.3) , (i6) , (d14.6)
c
c
c  Output:
c   strnums = a flag indicating the completion status of the routine.
c              0 = successful completion
c             -1 = which(1) is invalid
c             -2 = which(2) is invalid
c______________________________________________________________________________


      implicit none

      integer i,i1,i2,fnum,which(*)
      real r1,r2
      double precision d1,d2

      character*20 str1,str2
      character*41 string
      character*(*) form1,form2


c  Convert the first number to a string:

      if(which(1) .eq. 1)then
       write(str1,form1)i1

      elseif(which(1) .eq. 3)then
       write(str1,form1)r1

      elseif(which(1) .eq. 5)then
       write(str1,form1)d1

      else
       strnums = -1
       return

      endif


c  Convert the second number to a string:

      if(which(2) .eq. 2)then
       write(str2,form2)i2

      elseif(which(2) .eq. 4)then
       write(str2,form2)r2

      elseif(which(2) .eq. 6)then
       write(str2,form2)d2

      else
       strnums = -2
       return

      endif


c  Concatenate the second string number onto the first, and remove blanks:
      string = str1//char(9)//str2
      call strcrnch(string,i)


c  Write the string to the specified file:
      write(fnum,'(a)')string(1:i)

      strnums = 0

      return
      end
