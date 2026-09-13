#include "pch.h"
#include "SingleLL.h"

float sll::Distance(D2D1_POINT_2F first, D2D1_POINT_2F second)
{
	float a = (float)(pow(abs(second.x - first.x), 2));
	float b = (float)(pow(abs(second.y - first.y), 2));

	return (float)(sqrt(a + b));
}

void sll::Sort(LIST<D2D1_POINT_2F>& SortList, D2D1_POINT_2F ref, bool ascending)
{
	if (ascending)
	{
		if (SortList.size() < 2)return;
		else
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (size_t i = 0; i < SortList.size() - 1; ++i)
				{
					if (Distance(SortList[i], ref) > Distance(SortList[i + 1], ref))
					{
						D2D1_POINT_2F temp = SortList[i];
						SortList[i] = SortList[i + 1];
						SortList[i + 1] = temp;
						ok = false;
					}
				}
			}
		}
	}
	else
	{
		if (SortList.size() < 2)return;
		else
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (size_t i = 0; i < SortList.size() - 1; ++i)
				{
					if (Distance(SortList[i], ref) < Distance(SortList[i + 1], ref))
					{
						D2D1_POINT_2F temp = SortList[i];
						SortList[i] = SortList[i + 1];
						SortList[i + 1] = temp;
						ok = false;
					}
				}
			}
		}
	}
}
void sll::Sort(LIST<D2D1_RECT_F>& SortList, D2D1_RECT_F ref, bool ascending)
{
	D2D1_POINT_2F ref_center{ D2D1_POINT_2F(ref.left + (ref.right - ref.left) / 2.0f,
		ref.top + (ref.bottom - ref.top) / 2.0f) };

	if (SortList.size() < 2)return;
	else
	{
		if (ascending)
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (size_t i = 0; i < SortList.size() - 1; ++i)
				{
					D2D1_POINT_2F sort_center{ D2D1_POINT_2F(SortList[i].left + (SortList[i].right - SortList[i].left) / 2.0f,
						SortList[i].top + (SortList[i].bottom - SortList[i].top) / 2.0f) };
					D2D1_POINT_2F next_sort_center{ D2D1_POINT_2F(SortList[i + 1].left +
						(SortList[i + 1].right - SortList[i + 1].left) / 2.0f,
						SortList[i + 1].top + (SortList[i + 1].bottom - SortList[i + 1].top) / 2.0f) };

					if (Distance(sort_center, ref_center) > Distance(next_sort_center, ref_center))
					{
						D2D1_RECT_F temp{ SortList[i] };
						SortList[i] = SortList[i + 1];
						SortList[i + 1] = temp;
						ok = false;
					}
				}
			}
		}
		else
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (size_t i = 0; i < SortList.size() - 1; ++i)
				{
					D2D1_POINT_2F sort_center{ D2D1_POINT_2F(SortList[i].left + (SortList[i].right - SortList[i].left) / 2.0f,
						SortList[i].top + (SortList[i].bottom - SortList[i].top) / 2.0f) };
					D2D1_POINT_2F next_sort_center{ D2D1_POINT_2F(SortList[i + 1].left +
						(SortList[i + 1].right - SortList[i + 1].left) / 2.0f,
						SortList[i + 1].top + (SortList[i + 1].bottom - SortList[i + 1].top) / 2.0f) };

					if (Distance(sort_center, ref_center) < Distance(next_sort_center, ref_center))
					{
						D2D1_RECT_F temp{ SortList[i] };
						SortList[i] = SortList[i + 1];
						SortList[i + 1] = temp;
						ok = false;
					}
				}
			}
		}
	}
}