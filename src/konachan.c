#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "konachan.h"
#include "parser.h"
#include "yandere.h"

/* Given a https://konachan.com/ url,
 * parse the html to get the source image url
 */
char *konachan_get_image_url(char *web_content)
{
	/* constants used to find values */
	const char *png_source_uuid = "<li><a class=\"original-file-unchanged\" href=\"";
	const char *jpg_source_uuid = "<li><a class=\"original-file-changed\" href=\"";
	const char source_end = '"';
	const char *http = "http:";

	const unsigned int len_png = strlen(png_source_uuid);
	const unsigned int len_jpg = strlen(jpg_source_uuid);
	const unsigned int len_http = strlen(http);

	/* initialize the image source url to be returned later */
	char *img_src_url = NULL;

	/* initialize generic source image index */
	char *source_index = NULL;

	/* get png html pattern index and jpg html pattern index */
	char *png_index = strstr(web_content, png_source_uuid);
	char *jpg_index = strstr(web_content, jpg_source_uuid);

	/* find source image link */
	if (png_index)
		source_index = &(png_index[len_png]);
	else if (jpg_index)
		source_index = &(jpg_index[len_jpg]);

	/* check if any html pattern was detected */
	if (source_index) {
		/* get the length of the source image url */
		int url_len = get_distance(source_index, source_end);

		/* allocate enough memory to hold the image source url,
		 * then copy the url over to img_src_url and return it */
		img_src_url = malloc(sizeof(char) *
					(len_http + url_len + 1));

		strncpy(img_src_url, http, len_http);
		strncpy(&(img_src_url[len_http]), source_index, url_len);
		img_src_url[len_http + url_len] = '\0';
	}
	else {
		fprintf(stderr,
			"konachan_get_image_url(): Error: Failed to parse website\n");
	}

	/* return the image source url */
	return img_src_url;
}

struct image_tag_db *konachan_get_image_tags(char *web_content)
{
	struct image_tag_db *tag_db = yandere_get_image_tags(web_content);
	return tag_db;
}
