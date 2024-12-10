#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
bool DEAD = false;
bool WIN = false;
int main()
{
    initgraph(Col * IMGW, Row * IMGW, EW_SHOWCONSOLE);
    //播放开始音乐
    music();
    srand((unsigned int)time(NULL));

    int mine[Row][Col] = { 0 };//埋雷区数组

    Showmine(mine);

    //创造图片数组
    IMAGE img[13];

    for (int i = 0; i < 13; i++)
    {
        char filename[50] = { 0 };
        sprintf_s(filename, "./images/%d.gif", i);
        loadimage(img + i, filename, IMGW, IMGW);
    }
    //主函数*************************************
     //********************************************
    while (true)
    {
        //鼠标操作
        Mouseoperation(mine);
        //转换数组数据到图形
        drapmap(mine, img);
        //判断生死
        if (DEAD)//输了
        {
            int ret = MessageBox(GetHWnd(), "你踩到雷了！", "hit", MB_OKCANCEL);
            if (ret == IDOK)
            {
                Showmine(mine);
                DEAD = false;

            }
            else if (ret == IDCANCEL)
            {
                exit(502);
            }
        }
        else if (WIN)
        {
            drapmap(mine, img);
            int ret = MessageBox(GetHWnd(), "你赢了！是否再来一局？", "hit", MB_OKCANCEL);
            if (ret == IDOK)
            {
                Showmine(mine);
                WIN = false;
            }
            else if (ret == IDCANCEL)
            {
                exit(502);
            }

        }
        int count = 0;
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++)
            {
                if (mine[i][j] >= 0 && mine[i][j] <= 8)
                {
                    ++count;
                }
            }
        }
        if (count == Row * Col - Num)
        {
            WIN = true;
        }
    }
    

    getchar();
    return 0;
}


void music()
{
    PlaySound(TEXT("music\\back"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}



void showmap(int mine[Row][Col])//没问题
{
    //打印棋盘
    for (int a = 0; a < Row; a++)
    {
        for (int b = 0; b < Col; b++)
        {
            printf("%d ", mine[a][b]);
        }
        printf("\n");
    }
}



void Showmine(int mine[Row][Col])
{
    //把地图清零
    memset(mine, 0, Row * Col * sizeof(int));
    //埋雷
    for (int i = 0; i < Num;)
    {
        int x = rand() % Row;
        int y = rand() % Col;
        if (mine[x][y] == 0)
        {
            mine[x][y] = -1;
            i++;
        }
    }

    //计算雷数量
    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Col; j++)
        {
            if (mine[i][j] == -1)
            {
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if ((k >= 0 && k < Row && l >= 0 && l < Col) && mine[k][l] != -1)
                        {
                            mine[k][l]++;
                        }
                    }
                }
            }
        }
    }

    //全部加密
    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Col; j++)
        {
            mine[i][j] += 20;
        }
    }


}



void drapmap(int mine[Row][Col], IMAGE img[])
{
    for (int i = 0; i < Row; i++)
    {

        for (int j = 0; j < Col; j++)
        {
            if (mine[i][j] >= 0 && mine[i][j] <= 8)
            {
                putimage(j * IMGW, i * IMGW, img + mine[i][j]);
            }
            else if (mine[i][j] == -1)
            {
                putimage(j * IMGW, i * IMGW, img + 9);
            }
            else if (mine[i][j] == -2)
            {
                putimage(j * IMGW, i * IMGW, img + 12);
            }
            else if (mine[i][j] >= 19 && mine[i][j] <= 28)
            {
                putimage(j * IMGW, i * IMGW, img + 10);
            }
            else if (mine[i][j] >= 39 && mine[i][j] <= 48)
            {
                putimage(j * IMGW, i * IMGW, img + 11);
            }
        }
    }


}//转换数组数据到图形
void Mouseoperation(int mine[Row][Col])
{
    //定义消息结构体
    ExMessage msg;
    if (peekmessage(&msg, EM_MOUSE))
    {
        int r = msg.x / IMGW;
        int c = msg.y / IMGW;
        if (msg.message == WM_LBUTTONDOWN)//按左键
        {
            if (mine[c][r] >= 19 && mine[c][r] <= 28)
            {
                mine[c][r] -= 20;
                OpenNULL(mine, c, r);
                Findmine(mine, c, r);
                //打印雷区
                showmap(mine);

            }
        }
        else if (msg.message == WM_RBUTTONDOWN)//按右键插旗
        {
            if (mine[c][r] >= 19 && mine[c][r] <= 28)
            {
                mine[c][r] += 20;
            }
            else if (mine[c][r] >= 39)
            {
                mine[c][r] -= 20;
            }
        }

    }

}
void OpenNULL(int mine[Row][Col], int row, int col)
{//开空格
    if (mine[row][col] == 0)
    {
        for (int i = row - 1; i <= row + 1; i++)
        {
            for (int j = col - 1; j <= col; j++)
            {
                if ((i >= 0 && i <= Row && j >= 0 && j <= Col) && mine[i][j] >= 19 && mine[i][j] <= 28)
                {
                    mine[i][j] -= 20;
                    OpenNULL(mine, i, j);
                }
            }
        }
    }


}//
void Findmine(int mine[Row][Col], int row, int col)
{
    //点到雷游戏结束，其他雷显示
    if (mine[row][col] == -1)
    {
        mine[row][col] = -2;
        for (int i = 0; i < Row; i++)
        {
            for (int k = 0; k < Col; k++)
            {
                if (mine[i][k] == 19)
                {
                    mine[i][k] -= 20;
                }
            }
        }
        DEAD = true;
    }
}
