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
			KEY_t keys;
			VALUE_t values;
		public:
			GMap()
			{}

			VALUE_t Find(KEY_t)
			{
				for (int i{ 0 }; i < size; i++)
				{
					if (keys[i] == KEY_t)
						return values[i];
				}
			}
			
			~GMap()
			{}
		};		
	}
}
