#pragma once

#define MAP_WIDTH (7) //���̍ő喇��
#define MAP_HEIGHT (7)  //�c�̍ő喇��

/// <summary>
/// CSV�t�@�C���̓ǂݍ���
/// </summary>
/// <param name="map"> �ǂݍ���CSV�t�@�C���̕ۑ��� </param>
/// <param name="FilePath"> CSV�t�@�C���̃p�X </param>
/// <param name="LoadStopNumber"> �����Ɏw�肳�ꂽ�l���q�b�g����Ɠǂݍ��݂��I������ </param>
/// <returns> 0�ȊO�Ŏ��s�A0�Ő��� </returns>
int LoadCSV(int map[MAP_HEIGHT][MAP_WIDTH], const char* FilePath, int LoadStopNumber = -1);
