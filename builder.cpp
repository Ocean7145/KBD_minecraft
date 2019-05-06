

#include "pch.h"
#include <CoalaMOD.h>
#include <stdio.h>
#pragma warning(disable:4996)
#pragma comment(lib, "CoalaMOD.lib")


#define SWAP(x, y) { int t = x; x = y; y=t; } // 중간고사 문제에 나왔던 코드

// RlocateBlock은 지정되는 방향에 따라 블록이 다르게 놓이게 한다.
// 작은 값을 가지는 ex, ey, ez을 시작점으로 좌표와 블록이름, 방향과 gap을 전달받는다.
// 몇 가지가 걸려서 완성이 안 됐는데 지우기는 아까우니까 보류

/*
void RlocateBlock(BlockID block, int ex, int ey, int ez, int xgap, int zgap, int dir) // xgap과 zgap은 시작점으로부터 떨어진 위치.
{
	if (dir == 1) // 동쪽일 때. 이 쪽을 default로 한다.
	{
		locateBlock(block, ex, ey, ez);
	}
	else if (dir == 2) // 서쪽일 때. 이 쪽은 동쪽에 지어진 건물과 비교했을 때 x축이 반대방향이 되어야 한다.
	{
		locateBlock(block, ex - xgap, ey, ez);
	}
	else if (dir == 3)// 남쪽일 때. 이 쪽은 동쪽에 지어진 건물과 비교했을 때 x랑 z가 바뀌어야 한다.
	{
		locateBlock(block, ex + zgap, ey, ez + xgap);
	}
	else if (dir == 4)// 북쪽일 때. 이 쪽은 남쪽에 지어진 건물과 비교했을 때 gap의 연산 부호가 반대여야 한다.
	{
		locateBlock(block, ex - zgap, ey, ez -  xgap);
	}
} */

void rvlocate(BlockID block, int ex, int ey, int ez, int gap, int direction)
{
	if (direction == 0)
	{
		locateBlock(block, ex, ey, ez);
	}
	else
	{
		locateBlock(block, ex, ey, ez-(2*gap));
	}
}


int main()
{
	int sx, sy, sz, ex, ey, ez;
	// s-좌표들이 e-좌표들보다 큰 값을 가지도록 정렬
	int typenum; 
	int numbetx; //x축간격
	int numbety; //y축간격
	int numbetz;//z축간격
	int exmemory;
	int eymemory;
	int ezmemory;
	int height; // 가로등에서 쓰이는 변수
	int direction; // 방향 지정
	int error = 0; // 값 입력 오류 체크

	WoolID bw = createWool(COLOR_BLACK);
	WoolID yw = createWool(COLOR_YELLOW);
	FenceID dof = createFence(FENCE_DARK_OAK);
	TorchID torch = createTorch();
	BlockID gls = createBlock(BLOCK_GLOWSTONE);
	BlockID st = createBlock(BLOCK_STONE);
	PlanksID sp = createPlanks(PLANKS_SPRUCE);
	BlockID qz = createBlock(BLOCK_NETHER_QUARTZ);
	PaneID wp = createPane(COLOR_WHITE);
	SlabID ss = createSlab(SLAB_SPRUCE, SLAB_UPPER);
	SlabID qs = createSlab(SLAB_QUARTZ, SLAB_LOWER);
	PaneID np = createPane(PANE_GLASS);
	BlockID ng = createBlock(BLOCK_GLASS);
	SlabID qsu = createSlab(SLAB_QUARTZ, SLAB_UPPER);
	FenceID spf = createFence(FENCE_SPRUCE);
	PlantID spl = createPlant(PLANT_SPRUCE_LEAVES);
	BlockID grs = createBlock(BLOCK_GRASS);
	BlockID air = createBlock(BLOCK_AIR);
	PaneID irp = createPane(PANE_IRON);

	choose:
	printf("건설할 건축물의 종류를 결정하십시오. \n특정 건물들은 최소 입력값이 존재하며 모든 입력은 정수여야 합니다.\n");
	printf(" 1: 가로등\n 2: 주택\n 3: 도로\n 4: 프로그램 종료\n");
	scanf("%d", &typenum);

	if (typenum == 1) //가로등 건설하는 if구문
	{
		printf("\n가로등은 시작점의 좌표만 입력받으며, 방향을 입력받습니다. x축의 양의 방향을 동쪽으로 합니다.\n");
		input1:
		printf("가로등의 최소 높이는 4칸이어야 합니다.\n");
		printf("x1 좌표:");
		scanf("%d", &ex);
		printf("y1 좌표:");
		scanf("%d", &ey);
		printf("z1 좌표:");
		scanf("%d", &ez);
		printf("높이:");
		scanf("%d", &height);
		printf("방향을 입력하십시오 -  1: 동쪽, 2: 서쪽, 3: 남쪽, 4: 북쪽\n");
		scanf("%d", &direction);

		eymemory = ey;

		if (height < 4)
		{
			printf("높이가 너무 작습니다. 값을 다시 입력하십시오.");
			goto input1;
		}

		for (ey = eymemory; ey <= eymemory + height - 1; ey++)
			locateBlock(dof, ex, ey, ez);

		ey = eymemory;
		
		if (direction == 1)
		{
			locateBlock(dof, ex + 1, ey + height - 1, ez);
			locateBlock(gls, ex + 1, ey + height - 2, ez);

		}

		else if (direction == 2)
		{
			locateBlock(dof, ex - 1, ey + height - 1, ez);
			locateBlock(gls, ex - 1, ey + height - 2, ez);
		}

		else if (direction == 3)
		{
			locateBlock(dof, ex, ey + height - 1, ez + 1);
			locateBlock(gls, ex, ey + height - 2, ez + 1);
		}

		else if (direction == 4)
		{
			locateBlock(dof, ex, ey + height - 1, ez - 1);
			locateBlock(gls, ex, ey + height - 2, ez - 1);
		}

		else
		{
			printf(" 방향은 1, 2, 3, 4 중 하나로 입력되어야 합니다. 다시 입력하십시오. \n");
			goto input1;
		}

	
		printf("\n 건물 생성이 완료되었습니다. 건물 선택으로 돌아갑니다.\n\n");
		goto choose;
		
	}

	if (typenum == 2) // 1형 주택을 건설하는 if 구문
	{
		int xgap;
		int zgap;
		int county;
		printf(" 주택의 최소 x폭은 19칸, z폭은 14칸, y폭은 9칸입니다.\n");
		printf(" 최소 폭에 미달될 경우 건물이 생성되지 않습니다. \n\n");
		input2:
		printf("x1 좌표:");
		scanf("%d", &sx);
		printf("y1 좌표:");
		scanf("%d", &sy);
		printf("z1 좌표:");
		scanf("%d", &sz);
		printf("x2 좌표:");
		scanf("%d", &ex);
		printf("y2 좌표:");
		scanf("%d", &ey);
		printf("z2 좌표:");
		scanf("%d", &ez);

		if (ex > sx) SWAP(sx, ex);
		if (ey > sy) SWAP(sy, ey);
		if (ez > sz) SWAP(sz, ez);

		numbetx = sx - ex + 1; //x축간격
		numbety = sy - ey + 1; //y축간격
		numbetz = sz - ez + 1; //z축간격
		exmemory = ex;
		eymemory = ey;
		ezmemory = ez;

		if (numbetx < 19)
		{
			printf("x축 폭이 충분하지 않습니다. \n");
			error++;
		}
		if (numbetz < 14)
		{
			printf("z축 폭이 충분하지 않습니다. \n");
			error++;
		}
		if (numbety < 8)
		{
			printf("y축 폭이 충분하지 않습니다. \n");
			error++;
		}

		if (error >= 1)
		{
			printf("값을 재입력 하십시오.\n\n");
			goto input2;
		}
		/*
		else if (direction == 1) { //이 때는 e-좌표 중에서 z좌표만 큰 쪽에 감
			if (ex > sx) SWAP(sx, ex);
			if (ey > sy) SWAP(sy, ey);
			if (sz > ez) SWAP(ez, sz);


			numbetx = sx - ex + 1; //x축간격
			numbety = sy - ey + 1; //y축간격
			numbetz = ez - sz + 1; //z축간격
			exmemory = ex;
			eymemory = ey;
			ezmemory = ez;
		}

		/* else if (direction == 4) { //이 때는 e-좌표가 둘 다 큼
			if (sx > ex) SWAP(ex, sx);
			if (ey > sy) SWAP(sy, ey);
			if (sz > ez) SWAP(ez, sz);
		} */



		//시작점은 ex, ey, ez.  */

		for (ez = ezmemory; ez <= sz; ez++) //바닥에 까는 돌 만드는 반복문
		{
			for (ex = exmemory; ex <= sx; ex++)
			{
				locateBlock(st, ex, ey, ez);
			}
		}


		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 4 <= sz - 4; ez++) //윗쪽지붕 만드는 반복문
		{
			for (ex = exmemory; ex + 4 <= sx - 6; ex++)
			{
				locateBlock(qs, ex + 4, sy, ez + 4);
			}
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ex + 7 <= sx - 8; ex++) //위쪽 지붕 유리창 뒷쪽
		{
			locateBlock(np, ex + 7, sy - 1, sz - 5);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ex + 7 <= sx - 8; ex++) //위쪽 지붕 유리창 앞쪽
		{
			locateBlock(np, ex + 7, sy - 1, ez + 5);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 4 <= sz - 4; ez++) //위쪽 지붕 석영
		{
			locateBlock(qz, ex + 4, sy - 1, ez + 4);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 4 <= sz - 3; ez++)   //위쪽 지붕 바로 밑 천장
		{
			for (ex = exmemory; ex + 3 <= sx - 1; ex++)
			{
				locateBlock(qz, ex + 3, sy - 2, ez + 4);
			}
		}
		
		for (ex = exmemory, ey = eymemory, ez = ezmemory;ez+6 <= sz - 5; ez++) //내부 천장(반블록)
		{
			for (ex = exmemory; ex + 6 <= sx - 7; ex++)
			{
				locateBlock(qsu, ex + 6, sy - 2, ez + 6);
			}
		}
		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 5 <= sz - 4; ez++) //원래는 흰유리 써야하는데 흰유리가 없네. 지붕쪽 유리
		{
			for (ex = exmemory, county=4; county>=2; county--)
			{
				locateBlock(ng, sx - county, sy - 2, ez + 5);
			}
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 3; ey++) //뒤쪽 나무틀(세로)
		{
			locateBlock(sp, ex + 5, ey + 1, ez + 3);
			locateBlock(sp, ex + 5, ey + 1, ez + 4);
			locateBlock(sp, ex + 5, ey + 1, ez + 5);
			locateBlock(sp, sx - 6, ey + 1, ez + 3);
			locateBlock(sp, sx - 6, ey + 1, ez + 4);

		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ex + 6 <= sx - 7; ex++) // 뒤쪽 나무틀 (가로)
		{
			locateBlock(sp, ex + 6, sy - 3, ez + 4);
			locateBlock(ss, ex + 6, sy - 3, ez + 3);

		}
		
		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 4; ey++) //뒤쪽 유리판
		{
			for (ex = exmemory; ex + 6 <= sx - 7; ex++)
			{
				locateBlock(wp, ex + 6, ey + 1, ez + 4);
			}
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 3; ey++) //오른쪽 유리판
		{
			for (ez = ezmemory; ez + 5 <= sz - 5; ez++)
			{
				locateBlock(wp, sx - 6, ey + 1, ez + 5);
			}
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 3; ey++) //오른쪽 나무틀 + 기둥
		{
			locateBlock(sp, sx - 6, ey + 1, sz - 4);
			locateBlock(sp, sx - 6, ey + 1, sz - 3);
			locateBlock(spf, sx - 1, ey + 1, ez + 4);
			locateBlock(spf, sx - 1, ey + 1, sz - 3);

		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 3; ey++) //왼쪽 석영 틀
		{
			locateBlock(qz, ex + 3, ey + 1, ez + 4);
			locateBlock(qz, ex + 4, ey + 1, ez + 4);
			locateBlock(qz, ex + 3, ey + 1, sz - 3);
			locateBlock(qz, ex + 4, ey + 1, sz - 3); 
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 3; ey++) //왼쪽 나무틀(세로)
		{
			locateBlock(sp, ex + 5, ey + 1, sz - 3);
			locateBlock(sp, ex + 5, ey + 1, sz - 4);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 5 <= sz - 4; ez++) //왼쪽 나무틀(가로)
		{
			locateBlock(sp, ex + 5, sy - 3, ez + 5);
			locateBlock(ss, ex + 4, sy - 3, ez + 5);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 5 <= sz - 4; ez++) // 왼쪽 나뭇잎 + 풀바닥
		{
			locateBlock(spl, ex + 3, ey + 1, ez + 5);
			locateBlock(grs, ex + 3, ey, ez + 5);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey + 1 <= sy - 4; ey++) //왼쪽 유리창(세로)
		{
			locateBlock(wp, ex + 5, ey + 1, ez + 6);
			locateBlock(wp, ex + 5, ey + 1, sz - 5);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 6 <= sz - 5; ez++) //왼쪽 유리창(가로) + 발코니 나무바닥
		{
			locateBlock(wp, ex + 5, sy - 4, ez + 6);
			locateBlock(sp, ex + 4, ey, ez + 6);
		}

		for (ex = exmemory, ey = eymemory, ez = ezmemory; ey+ 1 <= sy - 3; ey++) //앞면유리 베이스
		{
			for (ex = exmemory; ex + 6 <= sx - 7; ex++)
			{
				locateBlock(wp, ex + 6, ey + 1, sz - 4);
			}
		}


		for (ex = exmemory, ey = eymemory, ez = ezmemory; ez + 5 <= sz - 5; ez++) //바닥까는거
		{
			for (ex = exmemory; ex + 6 <= sx - 7; ex++)
			{
				locateBlock(sp, ex + 6, ey, ez + 5);
			}
		}




		ex = exmemory; //이쪽 밑으로는 하나씩 놓고 마는 것들
		ey = eymemory;
		ez = ezmemory;

		locateBlock(air, sx - 9, ey + 1, sz - 4);
		locateBlock(air, sx - 9, ey + 2, sz - 4);
		locateBlock(air, sx - 9, ey + 3, sz - 4); //유리문 만드는 구멍을 내고

		locateBlock(wp, sx - 10, ey + 1, sz - 3);  
		locateBlock(irp, sx - 10, ey + 2, sz - 3);
		locateBlock(wp, sx - 10, ey + 3, sz - 3);
		locateBlock(wp, sx - 8, ey + 1, sz - 3);
		locateBlock(irp, sx - 8, ey + 2, sz - 3);
		locateBlock(wp, sx - 8, ey + 3, sz - 3);   //유리문(유리판+철창)


		locateBlock(sp, ex + 6, sy - 1, ez + 5);
		locateBlock(sp, sx - 7, sy - 1, ez + 5);
		locateBlock(sp, ex + 6, sy - 1, sz - 5);
		locateBlock(sp, sx - 7, sy - 1, sz - 5);
		locateBlock(spl, ex + 4, ey + 1, ez + 5);
		locateBlock(grs, ex + 4, ey , ez + 5);
		locateBlock(spl, ex + 4, ey + 1, sz - 4);
		locateBlock(grs, ex + 4, ey , sz - 4);


		printf("\n 건물 생성이 완료되었습니다. 건물 선택으로 돌아갑니다.\n\n");
		goto choose;
		
	}

	if (typenum == 3) //도로를 건설하는 if구문
	{
		printf("도로의 높이는 1로 고정되며 시작점의 y좌표를 따라갑니다.x축 간격과 z축 간격이 동일하면 안 됩니다.\n");
		printf("도로의 폭이 홀수일 때 중앙선은 1칸, 짝수일 때 2칸입니다.\n");
		input4:
		printf("x1 좌표:");
		scanf("%d", &sx);
		printf("y1 좌표:");
		scanf("%d", &ey);
		printf("z1 좌표:");
		scanf("%d", &sz);
		printf("x2 좌표:");
		scanf("%d", &ex);
		printf("z2 좌표:");
		scanf("%d", &ez);

		if (ex > sx) SWAP(sx, ex);
		if (ez > sz) SWAP(sz, ez);

		 numbetx = sx - ex + 1; //x축간격
		 numbetz = sz - ez + 1; //z축간격
		 exmemory = ex;
		 ezmemory = ez;


		 if (numbetx == numbetz)
		 {
			 printf("x축간격과 y축간격이 동일합니다. 값을 재입력 하십시오\n");
			 goto input4;
		 }


		for (; ez <= sz; ez++) {

			for (ex=exmemory; ex <= sx; ex++)
				locateBlock(bw, ex, ey, ez);
			
		}
		
		ex = exmemory;
		ez = ezmemory;

		if (numbetx > numbetz) // x축간격이 z축간격보다 클 경우
		{
			if (numbetz % 2 == 0) // 2에서 7까지면 2 3 4 5 6 7 에서 4 5에 생겨야 함. -1에서 4까지면 -1 0 1 2 3 4 에서 1 2 에 생겨야 함.
			{
				ez = ((sz + ez) - 1) / 2;

				for (ex = exmemory; ex <= sx; ex++)
					locateBlock(yw, ex, ey, ez);
				ez++;
				for (ex = exmemory; ex <= sx; ex++)
					locateBlock(yw, ex, ey, ez);
			}
			else // 2에서 8까지면 2 3 4 5 6 7 8 에서 5에 생겨야 함. 
			{
				ez = (sz + ez) / 2;
				for (ex = exmemory; ex <= sx; ex++)
					locateBlock(yw, ex, ey, ez);
			}
		}

		if (numbetz> numbetx) // z축간격이 x축간격보다 클 경우
		{
			if (numbetx % 2 == 0) // 2에서 7까지면 2 3 4 5 6 7 에서 4 5에 생겨야 함. -1에서 4까지면 -1 0 1 2 3 4 에서 1 2 에 생겨야 함.
			{
				ex = ((sx + ex) - 1) / 2;

				for (ez = ezmemory; ez <= sz; ez++)
					locateBlock(yw, ex, ey, ez);
				ex++;
				for (ez = ezmemory; ez <= sz; ez++)
					locateBlock(yw, ex, ey, ez);
			}
			else // 2에서 8까지면 2 3 4 5 6 7 8 에서 5에 생겨야 함. 
			{
				ex = (sx + ex) / 2;
				for (ez = ezmemory; ez <= sz; ez++)
					locateBlock(yw, ex, ey, ez);
			}
		}

		printf("\n 건물 생성이 완료되었습니다. 건물 선택으로 돌아갑니다.\n\n");
		goto choose;
	}


	if (typenum == 4) //프로그램 종료
		return 0;

}

