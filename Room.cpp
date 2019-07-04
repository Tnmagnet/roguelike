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
		env[i].setTexture(*texBg[i]);
	}
	//env[bgCnt].setTexture(*texBg[bgCnt]);�Ѿ�����������ѭ��
	for (int i = 0; i < tileCnt; i++) {
		env[i + 20].setTexture(*texTile[i]);
	}
}

void Room::generate() {
	//���ɷ��䱳���Ķ�������
	//���ɱر��ذ��ש
	hasGenerated = true;

	srand((unsigned int)time(NULL));
	int lastIndex=-1;
	for (float renderWidth = 0; renderWidth<1600;) {
		int a = rand() % 100;
		int index;
		if (a <= commenFactor) {
			index = COMMEN_BG;
		}
		else {
			index = (a - commenFactor) % (bgCnt-1);
		}
		//�ж��ظ���Ԫ
		if (index == COMMEN_BG && (lastIndex == COMMEN_BG || lastIndex == COMMEN_BG + 1)) {
			index = COMMEN_BG + 1;
		}
		lastIndex = index;
		bgIndexList1.push_back(index);
		renderWidth += env[index].getGlobalBounds().width;
	}
	lastIndex = -1;
	for (float renderWidth = 0; renderWidth < 1600;) {
		int a = rand() % 100;
		int index;
		if (a <= commenFactor) {
			index = COMMEN_BG;
		}
		else {
			index = (a - commenFactor) % (bgCnt-1);
		}
		//�ж��ظ���Ԫ
		if (index == COMMEN_BG && (lastIndex == COMMEN_BG || lastIndex == COMMEN_BG + 1)) {
			index = COMMEN_BG + 1;
		}
		lastIndex = index;
		bgIndexList2.push_back(index);
		renderWidth += env[index].getGlobalBounds().width;
	}
	lastIndex = -1;
	//���ɵ����ש
	for (float renderWidth = 0; renderWidth < 1600;) {
		int a = rand() % 5;
		int rep = rand() % 5;//�ظ�����
		int index = a;
		lastIndex = index;
		for (int j = 0; j < rep; j++) {
			tileIndexList.push_back(index);
			renderWidth += env[20 + index].getGlobalBounds().width;
		}
		
		
		

	}
}



void Room::draw(RenderWindow & win,const float levelHeight)
{
	float scaleFactorTile = 2.2;
	float scaleFactorBg = 2.5;//��ש�ͱ����ķŴ�����
	//���Ʒ��䱳������������
	float renderWidth = 0;
	for (vector<int>::iterator it = bgIndexList1.begin(); it != bgIndexList1.end(); it++) {
		const float thisHeight = env[*it].getGlobalBounds().height;
		env[*it].setPosition(static_cast<float>(renderWidth), 200 + levelHeight - thisHeight);
		env[*it].setScale(scaleFactorBg, scaleFactorBg);
		win.draw(env[*it]);
		renderWidth += env[*it].getGlobalBounds().width;
	}
	renderWidth = 0;
	for (vector<int>::iterator it = bgIndexList2.begin(); it != bgIndexList2.end(); it++) {
		const float thisHeight = env[*it].getGlobalBounds().height;
		env[*it].setPosition(static_cast<float>(renderWidth), 500 + levelHeight - thisHeight);
		env[*it].setScale(scaleFactorBg, scaleFactorBg);
		win.draw(env[*it]);
		renderWidth += env[*it].getGlobalBounds().width;
	}
	//���Ƶ����ש
	renderWidth = 0;
	for (vector<int>::iterator it = tileIndexList.begin(); it != tileIndexList.end(); it++) {
		const float thisHeight = env[*it].getGlobalBounds().height;
		env[*it+20].setPosition(static_cast<float>(renderWidth), 500 + levelHeight - thisHeight);
		env[*it + 20].setScale(scaleFactorTile, scaleFactorTile);
		win.draw(env[*it + 20]);
		renderWidth += env[*it + 20].getGlobalBounds().width;
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
	for (int i = 0; i < tileIndexList.size(); i++) {
		if (isIn(pos, env[i + 20].getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}





float Room::standPlace(FloatRect person)
{
	float ans = 999;//���շ���999����û�еط����Բ�
	float judgeX = person.left + person.width*0.5;//�ж���Ϊ�������ĵ�
	for (int i = 0; i < tileIndexList.size(); i++) {
		FloatRect thisBound = env[i + 20].getGlobalBounds();
		if (thisBound.left<judgeX&&thisBound.left + thisBound.width>judgeX) {
			ans = ans < thisBound.top ? ans : thisBound.top;
		}
	}
	return 0.0f;
}

Room::~Room()
{
	for (int i = 0; i < 20; i++) {
		delete texBg[i];
		delete texTile[i];
	}

}
