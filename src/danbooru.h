
/* given a danbooru url, parse it to generate a url
 * to a json version of the webpage
 */
char *danbooru_generate_api_url(char *url);

/* Given the html of a danbooru post webpage, parse the html
 * to get the source image url
 */
char *danbooru_get_image_url(char *html_content);

/* Given the json of a danbooru post webpage, parse the json
 * to get the source image url
 */
char *danbooru_get_image_url_json(char *json_content);

/* Given the html of a danbooru post webpage, parse the html
 * to get the tags of the image
 */
struct image_tag_db *danbooru_get_image_tags(char *html_content);

/* Given the json of a danbooru post webpage, parse the json
 * to get the tags of the image
 */
struct image_tag_db *danbooru_get_image_tags_json(char *json_content);

struct llnode *danbooru_parse_tags_json(char *tag_pattern, char *json_content,
	unsigned int *size);

unsigned int danbooru_get_tag_type(char category);
