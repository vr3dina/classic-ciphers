#include "Ciphers.h"
#include <algorithm>
#include <assert.h>

namespace Cipher {
	namespace  Playfair {

		static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,_";
		static std::string table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,_";
		const int row_cnt = 5;
		const int col_cnt = 6;

		static inline size_t index(char ch)
		{
			return table.find(ch);
		}
		
		void init_table(const std::string& key)
		{
			assert(row_cnt * col_cnt == table.size());
			table = key + alphabet;
			for (size_t i = 0; i < key.size(); i++)
			{
				table.erase(std::remove(table.begin() + i + 1, table.end(), key[i]), table.end());
			}
		}

		std::string encode(const std::string& key, const std::string& text)
		{
			init_table(key);
			std::string res = text;

			for (size_t i = 0, res_i = 0; i < text.size(); i += 2, res_i += 2)
			{
				bool skip = false;
				size_t fst = index(text[i]);
				size_t snd;

				if (i + 1 == text.size())
				{
					snd = table.size() - 1;
					res.resize(res.size() + 1);
				}
				else if (text[i] == text[i + 1])
				{
					snd = table.size() - 1;
					res.resize(res.size() + 1);
					skip = true;
				}
				else
				{
					snd = index(text[i + 1]);
				}


				int fst_row = fst / col_cnt;
				int snd_row = snd / col_cnt;
				int fst_col = fst % col_cnt;
				int snd_col = snd % col_cnt;

				if (fst_row == snd_row)
				{
					res[res_i] = table[(fst + 1) % col_cnt + fst_row * col_cnt];
					res[res_i + 1] = table[(snd + 1) % col_cnt + fst_row * col_cnt];
				}
				else if (fst_col == snd_col)
				{
					res[res_i] = table[((fst_row + 1) % row_cnt) * col_cnt + fst_col];
					res[res_i + 1] = table[((snd_row + 1) % row_cnt) * col_cnt + fst_col];
				}
				else
				{
					res[res_i] = table[fst_row * col_cnt + snd_col];
					res[res_i + 1] = table[snd_row * col_cnt + fst_col];
				}

				if (skip) i--;
			}

			return res;
		}

		std::string decode(const std::string& key, const std::string& text)
		{
			init_table(key);
			std::string res = text;

			for (size_t i = 0, res_i = 0; i < text.size(); i += 2, res_i += 2)
			{
				assert(text.size() % 2 == 0);
				size_t fst = index(text[i]);
				size_t snd = index(text[i + 1]);

				//if (i + 1 == text.size())
				//{
				//	snd = table.size() - 1;
				//	res.resize(res.size() + 1);
				//}
				//else if (text[i] == text[i + 1])
				//{
				//	snd = table.size() - 1;
				//	res.resize(res.size() + 1);
				//	skip = true;
				//}
				//else
				//{
				//	snd = index(text[i + 1]);
				//}


				int fst_row = fst / col_cnt;
				int snd_row = snd / col_cnt;
				int fst_col = fst % col_cnt;
				int snd_col = snd % col_cnt;

				if (fst_row == snd_row)
				{
					res[res_i] = table[(fst + col_cnt - 1) % col_cnt + fst_row * col_cnt];
					res[res_i + 1] = table[(snd + col_cnt - 1) % col_cnt + fst_row * col_cnt];
				}
				else if (fst_col == snd_col)
				{
					res[res_i] = table[((fst_row + row_cnt - 1) % row_cnt) * col_cnt + fst_col];
					res[res_i + 1] = table[((snd_row + row_cnt - 1) % row_cnt) * col_cnt + fst_col];
				}
				else
				{
					res[res_i] = table[fst_row * col_cnt + snd_col];
					res[res_i + 1] = table[snd_row * col_cnt + fst_col];
				}
			}
			res.erase(std::remove(res.begin(), res.end(), '_'), res.end());
			return res;
		}
	}
}

