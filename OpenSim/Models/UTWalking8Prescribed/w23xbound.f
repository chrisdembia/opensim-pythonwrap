      subroutine xmirror23(x,xb)
c=================================================================

      implicit none

      include 'w23params.h'
      integer i,j,k,l
      integer nmus2
      include 'w23comblk.h'

c Duplicate x for both sides of the body and store in xb:
      k = 1
      l = 1
      nmus2 = nmus / 2
      do i = 1,nnodes
        do j = 1,nmus2
          xb(l) = x(k)
          xb(nmus2+l) = x(k)
          k = k + 1
          l = l + 1 
        enddo
        l = l + nmus2 
      enddo
      xb(bndcntr) = tfinal
ccc      xb(bndcntr) = x(ncntr)

      return
      end





      subroutine xextract23(xb,x)
c=================================================================

      implicit none

      include 'w23params.h'
      integer i,j,k,l
      integer nmus2
      include 'w23comblk.h'

c Extract the controls from xb for one side of the body
c and store in x:
      k = 1
      l = 1
      nmus2 = nmus / 2
      do i = 1,nnodes
        do j = 1,nmus2
          x(k) = xb(l)
          k = k + 1
          l = l + 1 
        enddo
        l = l + nmus2
      enddo
ccc      x(ncntr) = xb(bndcntr)


      return
      end




      integer function intnode(dnode)
c===============================================================
      implicit none
      integer dnode

      intnode = dnode - 2
      if(intnode.lt.1) intnode = 1

      return
      end


      subroutine vtx(dnode,xv,x)
c===============================================================
      implicit none
      include 'w23params.h'
      integer i,index,dnode
      include 'w23comblk.h'

      index = (dnode-1) * nmus
      do i = 1,vcntr
        x(index+i) = xv(i)
      enddo

      return
      end


      subroutine xtv(dnode,x,xv)
c===============================================================
      implicit none
      include 'w23params.h'
      integer i,index,dnode
      include 'w23comblk.h'

      index = (dnode-1) * nmus
      do i = 1,vcntr
        xv(i) = x(index+i)
      enddo

      return  
      end





      subroutine xbound23(x,xb,ynode)
c===============================================================
      implicit none

      include 'w23params.h'
      integer i,j
      real*8 xdum(1000)
      include 'w23comblk.h'

      if(bndcntr .gt. 1000) then
        print*,'Error-  xdum in xbound23() not dimensioned'
      endif

c  Calculate the bounded initial activations
      do i = 1,nmus
        ynode(1,iatv+i) = 0.99d0/(1.d0+dexp(-x(i))) + 0.01d0
      enddo 
      call setmusfrc23(ynode)

c  Calculate bounded excitations:
      j=1
      do i = nmus+1,ncntr
        xb(j) = 0.99d0/(1.d0+dexp(-x(i))) + 0.01d0
        j=j+1
      enddo
c     Last equal first:
      do i = 1,nmushalf
        xb(bndcntr-1-nmus+i) = xb(nmushalf+i)
        xb(bndcntr-1-nmus+nmushalf+i) = xb(i)
      enddo
      xb(bndcntr) = tfinal


      return
      end



      subroutine xunbound23(xin,xout)
c==============================================================

      implicit none

      include 'w23params.h'
      integer i
      real*8 xin(ncntr),xout(ncntr)
      include 'w23comblk.h'

c  Check that the controls are all between 0.99 and 0.02:
      do i = 1,ncntr
        xin(i) = dmin1( 0.99999d0 , xin(i) )
        xin(i) = dmax1( 0.01001d0 , xin(i) )
      enddo

c  Calculate the unbounded controls
      do i = 1,ncntr
        xout(i) = -dlog(0.99d0/(xin(i)-0.01d0)-1.d0)
      enddo

      return
      end




