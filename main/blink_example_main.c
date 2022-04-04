/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "stdio.h"
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <sys/param.h>
#include "esp_netif.h"



#define EXAMPLE_ESP_WIFI_SSID_AP      "default_ssid"
#define EXAMPLE_ESP_WIFI_PASS_AP     "test12345"
#define EXAMPLE_ESP_WIFI_CHANNEL   1
#define EXAMPLE_MAX_STA_CONN       10


esp_netif_t* ap_netif_g;
esp_netif_t* sta_netif_g;

static void UART0_task(void *argument);
static bool ParseSystemCmd(char *line, uint16_t cmd_size);
static void WIFI_INIT_AP_STA();
static void STOP_WIFI_AP_STA();


void app_main(void)
{
    esp_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);


    WIFI_INIT_AP_STA();

    xTaskCreate(UART0_task,"UART0_task",10000,NULL,1,NULL); // receiving commands from main uart    

}






















static void UART0_task(void *argument)
{
  unsigned int char_received=EOF;
  unsigned int char_counter=0;
  char command_line[1024];
  for (;;)
	{

    while (char_received == EOF)
        {
          char_received=getchar(); 
		  vTaskDelay(10/portTICK_PERIOD_MS);

        }

				char c = (char)char_received;

				//if ((c == '\n') || (c == '\r')) { // End of line reached
				if (c == '\n') // End of line reached
				{ 
					command_line[char_counter] = 0; // Set string termination character.
					ParseSystemCmd(command_line, char_counter); // Line is complete. Execute it!
					char_counter = 0;
          			char_received=EOF;
				}
				else
				{
					if (c <= ' ')
					{

					}
					else
							if (char_counter >= (1024 - 1))
							{
								// Detect line buffer overflow. Report error and reset line buffer.
								char_counter = 0;

							}
							else
								if ((c >= 'A') && (c <= 'Z'))
								{ // Upcase lowercase
									command_line[char_counter++] = c - 'A' + 'a';
								}
								else
								{
									command_line[char_counter++] = c;
								}
				}

        char_received=EOF;

  }

}



static bool ParseSystemCmd(char *line, uint16_t cmd_size)
{

	if (!strncmp("stop_wifi_ap", line,12)){	
			STOP_WIFI_AP_STA();
            return true;
	}
	if (!strncmp("start_wifi_ap", line,13)){	
			WIFI_INIT_AP_STA();
            return true;
	}
    else
    {
    
	//ESP_LOGI("ERROR:" "System cmd not found: %s\r", line);
	return false;
    }
}   



static void WIFI_INIT_AP_STA(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ap_netif_g = esp_netif_create_default_wifi_ap();
    assert(ap_netif_g);

    sta_netif_g = esp_netif_create_default_wifi_sta();
    assert(sta_netif_g);
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID_AP,
            .ssid_len= strlen(EXAMPLE_ESP_WIFI_SSID_AP), 
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS_AP,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    if (strlen(EXAMPLE_ESP_WIFI_PASS_AP) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI("WIFI AP", "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             EXAMPLE_ESP_WIFI_SSID_AP, EXAMPLE_ESP_WIFI_PASS_AP, EXAMPLE_ESP_WIFI_CHANNEL);
   
}

static void STOP_WIFI_AP_STA(){
        esp_wifi_disconnect();            // break connection to AP
        esp_wifi_stop();                 // shut down the wifi radio
        esp_wifi_deinit();              // release wifi resources   
        esp_netif_destroy_default_wifi(ap_netif_g);
        esp_netif_destroy_default_wifi(sta_netif_g);
        esp_event_loop_delete_default();
        esp_netif_deinit();
}