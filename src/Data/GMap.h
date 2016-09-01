#pragma once

namespace ged
{
	namespace Data
	{
		/*
			GMap<string, int> voti;

			voti["Pippo"] = 7;
		*/

		template<typename KEY_t, typename VALUE_t>
		class GMap
		{
		private:
			int size;
			KEY_t* keys = nullptr;
			VALUE_t* values = nullptr;
		public:
			GMap(int size_mapper) //if dont want use lists
			{                     //better structured datas
			    if(size_mapper <= 0)
                    return;       //manage exception!

			    size = 0;
			    keys = new KEY_t    [size_mapper];
			    values = new VALUE_t[size_mapper];
			}
            void Add(KEY_t key, VALUE_t value)
            {
                keys[size] = key;
                values[size] = value;
                size++;
            }
			VALUE_t Find(KEY_t key_search)
			{
				for (int i = 0 ; i < size; i++)
				{
					if (keys[i] == key_search)
						return values[i];
				}
				return VALUE_t(); //manage exception!
			}
			VALUE_t operator[](KEY_t key_search)
			{
				return Find(key_search);
			}

			~GMap()
			{
                delete[] keys;
                delete[] values;
                size = 0;
			}
		};
	}
}
