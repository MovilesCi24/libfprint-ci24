#include <iostream>
#include <fprint.h>
#include <unistd.h>

using namespace std;


struct fp_dscv_dev *discover_device(struct fp_dscv_dev **discovered_devs)
{
	struct fp_dscv_dev *ddev = discovered_devs[0];
	struct fp_driver *drv;
	if (!ddev)
		return NULL;
	
	drv = fp_dscv_dev_get_driver(ddev);
	cout << "Found device claimed by" << fp_driver_get_full_name(drv) << " driver" << endl;
	return ddev;
}

struct fp_dev *initialize_fp() {
	cout << "Initializing fingerprint" << endl;
	int r = 1;
	r = fp_init();

	if (r < 0) {
		cout << "Error initializing fprint" << endl;
		fp_exit();
		return NULL;
	}
	
	cout << "fprint initialized!" << endl;

	struct fp_dscv_dev **discovered_devs;	
	discovered_devs = fp_discover_devs();
	if (!discovered_devs) {
		cout <<  "Could not discover devices" << endl;
		fp_exit();
		return NULL;
	}
	cout << "Devices discovered" << endl;
	
	struct fp_dscv_dev *ddev;
	ddev = discover_device(discovered_devs);
	if (!ddev) {
		fp_dscv_devs_free(discovered_devs);
		cout << "No devices detected" << endl;
		fp_exit();
		return NULL;
	}

	struct fp_dev *dev;
	dev = fp_dev_open(ddev);
	fp_dscv_devs_free(discovered_devs);
	if (!dev) {
		cout << "Could not open device" << endl;
		fp_exit();
		return NULL;
	}

	if (!fp_dev_supports_imaging(dev)) {
		cout << "this device does not have imaging capabilities" << endl;
		fp_dev_close(dev);
		fp_exit();
		return NULL;	
	}

	cout << "Changing enroll stages count number" << endl;
	fpi_dev_set_nr_enroll_stages(dev, 2);
	// Set enroll stages manually
	// dev->nr_enroll_stages = 2;

	cout << "Opened device. It's now time to scan your finger" << endl;

	return dev;
}

int verify() {
	cout << "Initializing verify" << endl;

	int r = 1; 

	struct fp_dev* dev = initialize_fp();
	
	if (dev == NULL) {
		cout << "Error initializing fingerprint" << endl;
		return 1;
	}

	struct fp_img *img = NULL;

	struct fp_print_data *enrolled_print;
	int finger_code = 3;
	cout << "Loading fingerprint " << 3;
	r = fp_print_data_load(dev, finger_code, &enrolled_print);

	if (r < 0) {
		cout << "Loading fingerprint failed with error " << r << endl;	
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}

	struct fp_print_data *print_gallery[1];
	print_gallery[0] = enrolled_print;
	
	cout << "Calling image identification" << endl;
	size_t offset;
	r = fp_identify_finger_img(dev, print_gallery, &offset, &img);

	switch (r) {
		case FP_VERIFY_NO_MATCH:
			cout <<"NO MATCH!" << endl;
			break;
		case FP_VERIFY_MATCH:
			cout <<"MATCH! Offset: " << offset << endl;
			break;
		case FP_VERIFY_RETRY:
			cout <<"Scan didn't quite work. Please try again" << endl;
			break;
		case FP_VERIFY_RETRY_TOO_SHORT:
			cout <<"Swipe was too short, please try again" << endl;
			break;
		case FP_VERIFY_RETRY_CENTER_FINGER:
			cout <<"Please center your finger on the sensor and try again" << endl;
			break;
		case FP_VERIFY_RETRY_REMOVE_FINGER:
			cout <<"Please remove finger from the sensor and try again" << endl;
			break;
	}

	// Done - Freeing resources
	r = 0;
	cout << "Closing" << endl;
	fp_dev_close(dev);
	fp_exit();
	return 0;

}

int enroll() {
	cout << "Initializing enroll" << endl;

	int r = 1; 

	struct fp_dev* dev = initialize_fp();
	
	if (dev == NULL) {
		cout << "Error initializing fingerprint" << endl;
		return 1;
	}

	struct fp_img *img = NULL;

	struct fp_print_data *enrolled_print;
	cout << "You need to scan your finger " << fp_dev_get_nr_enroll_stages(dev) << " to complete the process" << endl;

	while(true) {
		usleep(1 * 1000 * 1000);
		cout << "Scan your finger now" << endl;


		// Enroll routine
		r = fp_enroll_finger_img(dev, &enrolled_print, &img);
		if (img) {
			fp_img_save_to_file(img, "enrolled.pgm");
			cout << "Wrote scanned image to enrolled.pgm" << endl;
			fp_img_free(img);
		}
		if (r < 0) {
			cout << "Enroll failed with error " << r << endl;	
			fp_dev_close(dev);
			fp_exit();
			return 1;
		}

		switch (r) {
			case FP_ENROLL_COMPLETE:
				cout << "Enroll complete!" << endl;
				break;
			case FP_ENROLL_FAIL:
				cout << "Enroll failed, something wen't wrong" << endl;
				break;
			case FP_ENROLL_PASS:
				cout << "Enroll stage passed. Yay!" << endl;
				break;
			case FP_ENROLL_RETRY:
				cout << "Didn't quite catch that. Please try again" << endl;
				break;
			case FP_ENROLL_RETRY_TOO_SHORT:
				cout << "Your swipe was too short, please try again" << endl;
				break;
			case FP_ENROLL_RETRY_CENTER_FINGER:
				cout <<"Didn't catch that, please center your finger on the sensor and try again" << endl;
				break;
			case FP_ENROLL_RETRY_REMOVE_FINGER:
				cout << "Scan failed, please remove your finger and then try again." << endl;
				break;
		}

		if (r == FP_ENROLL_FAIL || r == FP_ENROLL_COMPLETE) {
			break;
		}
	}

	if (r != FP_ENROLL_COMPLETE) {
		cout << "Uninitializing device" << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}

	// Saving fingerprint 
	cout << "Saving data into disk" << endl;
	r = fp_print_data_save(enrolled_print, 3);
	if (r < 0) {
		cout <<"Cannot save enrolled print image" << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	

	// Verify routine
	usleep(1 * 100 * 1000);
	cout << "Now we are using device for verify" << endl;

	cout <<"Scan your finger now" << endl;
	r = fp_verify_finger_img(dev, enrolled_print, &img);
	if (img) {
		fp_img_save_to_file(img, "verify.pgm");
		cout <<"Wrote scanned image to verify.pgm" << endl;
		fp_img_free(img);
	}

	if (r < 0) {
		cout <<"verification failed with error" << endl;
		fp_dev_close(dev);
		fp_exit();
		return r;	
	}

	switch (r) {
	case FP_VERIFY_NO_MATCH:
		cout <<"NO MATCH!" << endl;
		break;
	case FP_VERIFY_MATCH:
		cout <<"MATCH!" << endl;
		break;
	case FP_VERIFY_RETRY:
		cout <<"Scan didn't quite work. Please try again" << endl;
		break;
	case FP_VERIFY_RETRY_TOO_SHORT:
		cout <<"Swipe was too short, please try again" << endl;
		break;
	case FP_VERIFY_RETRY_CENTER_FINGER:
		cout <<"Please center your finger on the sensor and try again" << endl;
		break;
	case FP_VERIFY_RETRY_REMOVE_FINGER:
		cout <<"Please remove finger from the sensor and try again" << endl;
		break;
	}

	// Done - Freeing resources
	r = 0;
	cout << "Closing" << endl;
	fp_dev_close(dev);
	fp_exit();
	return 0;
}

int scan() {
	cout << "Initializing scan" << endl;
	
	int r = 1; 

	struct fp_dev* dev = initialize_fp();
	
	if (dev == NULL) {
		cout << "Error initializing fingerprint" << endl;
		return 1;
	}
	
	struct fp_img *img = NULL;
	r = fp_dev_img_capture(dev, 0, &img);
	if (r) {
		cout << "image capture failed, code " << r << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;	
	}

	r = fp_img_save_to_file(img, "finger.pgm");
	if (r) {
		cout << "img save failed, code " << r << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}	

	fp_img_standardize(img);
	r = fp_img_save_to_file(img, "finger_standardized.pgm");
	fp_img_free(img);
	if (r) {
		cout << "standardized img save failed, code " << r << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	
	r = 0;
	cout << "Done!" << endl;
	fp_dev_close(dev);
	fp_exit();
	return 0;
}

void sync_capture_cb(struct fp_dev *dev, int result, struct fp_img *img, void *user_data)
{
	cout << "Image is captured" << endl;
	cout << "Saving image" << endl;

	// Done!
	int r = fp_img_save_to_file(img, "finger.pgm");
	if (r) {
		cout << "img save failed, code " << r << endl;
	}		
}

void capture_stop_cb(struct fp_dev *dev, void *user_data) {
	cout << "Stopped" << endl;
}


int scan_async() {
	cout << "Initializing scan async test" << endl;

	int r = 1; 

	struct fp_dev* dev = initialize_fp();
	
	if (dev == NULL) {
		cout << "Error initializing fingerprint" << endl;
		return 1;
	}

	cout << "Generating calling function" << endl;
	int unconditional = 0;
    r = fp_async_capture_start(dev, unconditional, sync_capture_cb, NULL);

	if (r < 0) {
		cout << "Error starting capture" << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	
	cout << "Waiting 5 seconds and then stop" << endl;
	usleep(5 * 1000 * 1000);

	r = fp_async_capture_stop(dev, capture_stop_cb, NULL);
	
	fp_async_capture_stop(dev, capture_stop_cb, NULL);
	cout << "Waiting 5 seconds and start again" << endl;
	usleep(5 * 1000 * 1000);
	r = fp_async_capture_start(dev, unconditional, sync_capture_cb, NULL);

	if (r < 0) {
		cout << "Error starting capture" << endl;
		fp_dev_close(dev);
		fp_exit();
		return 1;
	}
	
	cout << "Waiting 5 seconds and then stop" << endl;
	usleep(5 * 1000 * 1000);

	r = fp_async_capture_stop(dev, capture_stop_cb, NULL);
	
	
	cout << "Done!" << endl;
}



int main() {
	cout << "Initializing main function" << endl;
	return scan();

}

