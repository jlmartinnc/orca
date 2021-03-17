#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  client *client = config_init(config_file);
  assert(NULL != client);

  user::dati *me = user::dati_alloc(); 
  assert(NULL != me);

  user::get_current_user::run(client, me);
  printf("Greetings, %s#%s!\n", me->username, me->discriminator);

  NTL_T(guild::dati) guilds = NULL;
  user::get_current_user_guilds::run(client, &guilds);
  for (size_t i=0; guilds[i]; ++i) {
    fprintf(stderr, "Guild[%s] id:\n\t%" PRIu64 "\n", guilds[i]->name, guilds[i]->id);
  }

  guild::dati_list_free(guilds);
  user::dati_free(me);

  cleanup(client);

  global_cleanup();
}
