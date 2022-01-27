#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStubOK(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    return 200;
}


int networkAlertStubNotOK(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    return 500;
}

void alertInCelcius(float farenheit,int (*networkAlert)(float)) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlert(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    int (*funp_networkalert)(float) = networkAlertStubOK; //use networkAlertStub in test environment and xxnetworkAlertxx in real environment 
    alertInCelcius(400.5,funp_networkalert);
    alertInCelcius(303.6,funp_networkalert);
    
    (*funp_networkalert)(float) = networkAlertStubNotOK;
    alertInCelcius(1000,funp_networkalert);
    assert(alertFailureCount == 1);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
