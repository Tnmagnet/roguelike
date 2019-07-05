#include "Room.h"
#define COMMEN_BG 9
bool Room::getHasGenerated()
{
	return hasGenerated;
}
Room::Room(const int _bgCnt, const int _tileCnt, string bgRootPath, string tileRootPath)
{
	bgCnt = _bgCnt;
	tileCnt = _tileCnt;
	string bgPath[20];
	string tilePath[20];
	//��������
	for (int i = 0; i < 20; i++) {
		texBg[i] = new Texture;
		texTile[i] = new Texture;
	}
	for (int i = 0; i <= bgCnt; i++) {//10��ͼ���10��Ϊ����ͼ����ʮһ��Ϊ���ظ���Ԫ
		bgPath[i] = bgRootPath + to_string(i)+".png";
		texBg[i]->loadFromFile(bgPath[i].c_str());
	}
	
	for (int i = 0; i < tileCnt; i++) {
		tilePath[i] = tileRootPath + "0" + to_string(i)+".png";
		texTile[i]->loadFromFile(tilePath[i].c_str());
	}
	//���������
	for (int i = 0; i <= bgCnt; i++) {
		bg[i].setTexture(*texBg[i]);
	}
	//env[bgCnt].setTexture(*texBg[bgCnt]);�Ѿ�����������ѭ��
	for (int i = 0; i < tileCnt; i++) {
		tile[i].setTexture(*texTile[i]);
	}
}

void Room::generate() {
	//���ɷ��䱳���Ķ�������
	//���ɱر��ذ��ש
	hasGenerated = true;

	srand((unsigned int)time(NULL));
	int lastIndex = -1;
	for (float renderWidth = 0; renderWidth < 1700;) {
		int a = rand() % 100;
		int index;
		if (a <= commenFactor) {
			index = COMMEN_BG;
		}
		else {
			index = (a - commenFactor) % (bgCnt - 1);
		}
		//�ж��ظ���Ԫ
		if (index == COMMEN_BG && (lastIndex == COMMEN_BG || lastIndex == COMMEN_BG + 1)) {
			index = COMMEN_BG + 1;
		}
		lastIndex = index;
		bgIndexList1.push_back(index);
		renderWidth += bg[index].getGlobalBounds().width;
	}
	lastIndex = -1;
	for (float renderWidth = 0; renderWidth < 1700;) {
		int a = rand() % 100;
		int index;
		if (a <= commenFactor) {
			index = COMMEN_BG;
		}
		else {
			index = (a - commenFactor) % (bgCnt - 1);
		}
		//�ж��ظ���Ԫ
		if (index == COMMEN_BG && (lastIndex == COMMEN_BG || lastIndex == COMMEN_BG + 1)) {
			index = COMMEN_BG + 1;
		}
		lastIndex = index;
		bgIndexList2.push_back(index);
		renderWidth += bg[index].getGlobalBounds().width;
	}
	lastIndex = -1;
	//���ɵ����ש/¥��
	for (float renderWidth = 0; renderWidth < 4000;) {
		int a = rand() % tileCnt;
		while (a == 6 && lastIndex != 5) {
			a = rand() % tileCnt;
		}
		int rep = rand() % 3 + 1;//�ظ�����
		cout << "���� " << a << " �ظ����� " << rep << endl;
		int index =  a;
		lastIndex = index;
		for (int j = 0; j < rep; j++) {
			tileIndexList.push_back(index);
			tile[index].setScale(scaleFactorTile, scaleFactorTile);
			renderWidth += tile[index].getGlobalBounds().width;
		}
	}

	//���Ƶ���/¥�ݴ�ש
	
}





void Room::drawBg(RenderWindow & win)
{
	//const float levelHeight = 250;
	float scaleFactorTile = 2.2;
	float scaleFactorBg = 2.5;//�����ķŴ�����
	//���Ʒ��䱳������������
	float renderWidth = 0;
	for (vector<int>::iterator it = bgIndexList1.begin(); it != bgIndexList1.end(); it++) {
		const float thisHeight = bg[*it].getGlobalBounds().height;
		bg[*it].setPosition(renderWidth, 450 - thisHeight);
		bg[*it].setScale(scaleFactorBg, scaleFactorBg);
		win.draw(bg[*it]);
		renderWidth += bg[*it].getGlobalBounds().width;
	}
	renderWidth = 0;
	for (vector<int>::iterator it = bgIndexList2.begin(); it != bgIndexList2.end(); it++) {
		const float thisHeight = bg[*it].getGlobalBounds().height;
		bg[*it].setPosition(renderWidth, 750 - thisHeight);
		bg[*it].setScale(scaleFactorBg, scaleFactorBg);
		win.draw(bg[*it]);
		renderWidth += bg[*it].getGlobalBounds().width;
	}
	
}
void Room::drawTile(RenderWindow & win)
{	//ÿ�ζ����²����ԭ����ͬһ��tile���ܱ���Ⱦ����ͬ�ĵط�
	float renderWidth = 0;
	int offset = 0;//���ÿ�ִ�ש�Ĳ�ͬ�Ż�
	for (vector<int>::iterator it = tileIndexList.begin(); it != tileIndexList.end(); it++) {
		const float thisHeight = tile[*it].getGlobalBounds().height;
		switch (*it) {
		case 0:
		case 1:
		case 2:
		case 3:
			offset = 710;
			break;
		case 4:
			offset = 710;
			break;
		case 5:
		case 6:
			offset = 695;
			break;
		}
		tile[*it].setPosition(renderWidth, offset - thisHeight);
		renderWidth += tile[*it].getGlobalBounds().width;
		win.draw(tile[*it]);
	}
}
bool isIn(Vector2f pos, FloatRect tileRect)
{
	if (pos.x > tileRect.left&&pos.x<tileRect.left + tileRect.width
		&&pos.y>tileRect.top&&pos.y < tileRect.top + tileRect.height)return true;
	return false;
}
bool Room::isTile(Vector2f pos)
//�ж��Ƿ��Ǵ�ש
{
	float offset;
	float renderWidth = 0;
	for (vector<int>::iterator it = tileIndexList.begin(); it != tileIndexList.end(); it++) {
		const float thisHeight = tile[*it].getGlobalBounds().height;
		switch (*it) {
		case 0:
		case 1:
		case 2:
		case 3:
			offset = 710;
			break;
		case 4:
			offset = 710;
			break;
		case 5:
		case 6:
			offset = 695;
			break;
		}
		tile[*it].setPosition(renderWidth, offset - thisHeight);
		renderWidth += tile[*it].getGlobalBounds().width;
		if (isIn(pos, tile[*it].getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

float Room::standPlace(FloatRect person)
{
	float offset;
	float renderWidth = 0;
	float ans = -1;//���շ���-1����û�еط����Բ�
	float judgeX = person.left + person.width*0.5;//�ж���Ϊ�������ĵ�
	for (vector<int>::iterator it = tileIndexList.begin(); it != tileIndexList.end(); it++) {
		const float thisHeight = tile[*it].getGlobalBounds().height;
		switch (*it) {
		case 0:
		case 1:
		case 2:
		case 3:
			offset = 710;
			break;
		case 4:
			offset = 710;
			break;
		case 5:
		case 6:
			offset = 695;
			break;
		}
		tile[*it].setPosition(renderWidth, offset - thisHeight);
		renderWidth += tile[*it].getGlobalBounds().width;
		FloatRect thisBound = tile[*it].getGlobalBounds();
		if (thisBound.left<judgeX&&thisBound.left + thisBound.width>judgeX) {
			ans = ans < thisBound.top ? ans : thisBound.top;
		}
	}
	return ans;
}

Room::~Room()
{
	for (int i = 0; i < 20; i++) {
		delete texBg[i];
		delete texTile[i];
	}

}
