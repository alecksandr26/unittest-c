/*
  @file hashdates.c
  @brief This is the source implementation of the component of 'unittest_hashdates.h'.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License.
*/

#include "../include/unittest_debug.h"
#include "../include/unittest_def.h"
#include "../include/unittest_dir.h"
#include "../include/unittest_hashdates.h"
#include "../include/unittest_tfile.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <trycatch.h>
#include <unistd.h>

bool   dumped			    = false;
size_t unittest_amount_hashed_dates = 0;
long   unittest_hashed_dates[MAX_AMOUNT_OF_TEST_FILES];

/* scatter is a 256 entry array that maps bytes to random numbers. */
static unsigned long scatter[] = {
	2078917053, 143302914,	1027100827, 1953210302, 755253631,  2002600785,
	1405390230, 45248011,	1099951567, 433832350,	2018585307, 438263339,
	813528929,  1703199216, 618906479,  573714703,	766270699,  275680090,
	1510320440, 1583583926, 1723401032, 1965443329, 1098183682, 1636505764,
	980071615,  1011597961, 643279273,  1315461275, 157584038,  1069844923,
	471560540,  89017443,	1213147837, 1498661368, 2042227746, 1968401469,
	1353778505, 1300134328, 2013649480, 306246424,	1733966678, 1884751139,
	744509763,  400011959,	1440466707, 1363416242, 973726663,  59253759,
	1639096332, 336563455,	1642837685, 1215013716, 154523136,  593537720,
	704035832,  1134594751, 1605135681, 1347315106, 302572379,  1762719719,
	269676381,  774132919,	1851737163, 1482824219, 125310639,  1746481261,
	1303742040, 1479089144, 899131941,  1169907872, 1785335569, 485614972,
	907175364,  382361684,	885626931,  200158423,	1745777927, 1859353594,
	259412182,  1237390611, 48433401,   1902249868, 304920680,  202956538,
	348303940,  1008956512, 1337551289, 1953439621, 208787970,  1640123668,
	1568675693, 478464352,	266772940,  1272929208, 1961288571, 392083579,
	871926821,  1117546963, 1871172724, 1771058762, 139971187,  1509024645,
	109190086,  1047146551, 1891386329, 994817018,	1247304975, 1489680608,
	706686964,  1506717157, 579587572,  755120366,	1261483377, 884508252,
	958076904,  1609787317, 1893464764, 148144545,	1415743291, 2102252735,
	1788268214, 836935336,	433233439,  2055041154, 2109864544, 247038362,
	299641085,  834307717,	1364585325, 23330161,	457882831,  1504556512,
	1532354806, 567072918,	404219416,  1276257488, 1561889936, 1651524391,
	618454448,  121093252,	1010757900, 1198042020, 876213618,  124757630,
	2082550272, 1834290522, 1734544947, 1828531389, 1982435068, 1002804590,
	1783300476, 1623219634, 1839739926, 69050267,	1530777140, 1802120822,
	316088629,  1830418225, 488944891,  1680673954, 1853748387, 946827723,
	1037746818, 1238619545, 1513900641, 1441966234, 367393385,  928306929,
	946006977,  985847834,	1049400181, 1956764878, 36406206,   1925613800,
	2081522508, 2118956479, 1612420674, 1668583807, 1800004220, 1447372094,
	523904750,  1435821048, 923108080,  216161028,	1504871315, 306401572,
	2018281851, 1820959944, 2136819798, 359743094,	1354150250, 1843084537,
	1306570817, 244413420,	934220434,  672987810,	1686379655, 1301613820,
	1601294739, 484902984,	139978006,  503211273,	294184214,  176384212,
	281341425,  228223074,	147857043,  1893762099, 1896806882, 1947861263,
	1193650546, 273227984,	1236198663, 2116758626, 489389012,  593586330,
	275676551,  360187215,	267062626,  265012701,	719930310,  1621212876,
	2108097238, 2026501127, 1865626297, 894834024,	552005290,  1404522304,
	48964196,   5816381,	1889425288, 188942202,	509027654,  36125855,
	365326415,  790369079,	264348929,  513183458,	536647531,  13672163,
	313561074,  1730298077, 286900147,  1549759737, 1699573055, 776289160,
	2143346068, 1975249606, 1136476375, 262925046,	92778659,   1856406685,
	1884137923, 53392249,	1735424165, 1602280572};

/* unittest_hash: To hash some string and return some random unsinged integer */
unsigned long unittest_hash(const char *data)
{
	unsigned long h;
	int	      i;
	size_t	      len = strlen((char *) data);

	assert(len > 0 && "Invalid data lenght");

	for (h = 0, i = 0; i < (int) len; i++)
		h = (h << 1) + scatter[(unsigned char) data[i]];

	return h;
}

/* unittest_get_creation_date: This function gets the creation time of a file located at a
   given path and stores it as a string in the date parameter. */
void unittest_get_creation_date(const char *path_file, char *date)
{
	struct stat attr;

	assert(date != NULL && path_file != NULL && "You can't pass null arguemnt");

	/* TODO: Check if the file exist */

	stat(path_file, &attr);
	sprintf(date, "Last modified time: %s", ctime(&attr.st_mtime));
}

/* unittest_put_new_dates: Puts new creation/modification dates of the test files in the
 * file. */
void unittest_put_new_dates(void)
{
	FILE *fp;

	if ((fp = fopen(unittest_hashed_file, "wb")) == NULL)
		ABORT("Error opening the hashdates file \"%s\": errno: %s\n",
		      unittest_hashed_file, strerror(errno));

	/* Read the hashed binaries*/
	if (fwrite(&unittest_tfile_count, sizeof(size_t), 1, fp) != 1)
		ABORT("Error writing the hashdates file \"%s\": errno: %s\n",
		      unittest_hashed_file, strerror(errno));

	for (size_t i = 0; i < unittest_tfile_count; i++)
		if (fwrite(&unittest_tfiles[i].date_hashed, sizeof(long), 1, fp) != 1)
			ABORT("Error writing the hashdates file \"%s\": errno: %s\n",
			      unittest_hashed_file, strerror(errno));
	fclose(fp);
}

/* unittest_get_prev_dates: Gets the previous modification dates of a file in a specific
 * directory.
 */
void unittest_get_prev_dates(void)
{
	FILE *fp;

	if (dumped != false) return; /* Finish the function */
	dumped = true;

	if (access(unittest_hashed_file, F_OK) == -1) /* Doens't exist the file */
		return;

	if ((fp = fopen(unittest_hashed_file, "rb")) == NULL)
		ABORT("Error opening the hashdates file \"%s\": errno: %s\n",
		      unittest_hashed_file, strerror(errno));

	/* Read the hashed binaries*/
	if (fread(&unittest_amount_hashed_dates, sizeof(size_t), 1, fp) != 1)
		ABORT("Error reading the hashdates file \"%s\": errno: %s\n",
		      unittest_hashed_file, strerror(errno));

	if (fread(unittest_hashed_dates, sizeof(long), unittest_amount_hashed_dates,
		  fp) != unittest_amount_hashed_dates)
		ABORT("Error reading the hashdates file \"%s\": errno: %s\n",
		      unittest_hashed_file, strerror(errno));

	fclose(fp);
}
