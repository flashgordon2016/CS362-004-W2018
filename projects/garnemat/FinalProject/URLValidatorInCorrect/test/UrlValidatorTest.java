
 
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!







public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
	   //String[] schemes = {"http", "https", "ftp"};
	   
	  
	   
	   // Using default constructor
	   UrlValidator testVal1 = new UrlValidator();
	   
	   System.out.println("Testing isValid with default constructor");
	   
	   
	   
	   System.out.println("http://www.google.com: " + testVal1.isValid("http://www.google.com"));
	   System.out.println("https://www.google.com: " + testVal1.isValid("https://www.google.com"));
	   System.out.println("ftp://www.google.com: " + testVal1.isValid("ftp://www.google.com"));
	   System.out.println("test://www.google.com: " + testVal1.isValid("test://www.google.com"));
	   System.out.println("www.google.com: " + testVal1.isValid("www.google.com"));
	   System.out.println("http://255.255.255.255: " + testVal1.isValid("http://255.255.255.255"));
	   System.out.println("http://256.256.256.256: " + testVal1.isValid("http://256.256.256.256"));
	   System.out.println("http://www.google.com/hello?key=value: " + testVal1.isValid("http://www.google.com/hello?key=value"));
	   System.out.println("http://www.google.com:20/hello?key=value: " + testVal1.isValid("http://www.google.com:20/hello?key=value"));
	   System.out.println("http://www.google.com:20:" + testVal1.isValid("http://www.google.com:20"));
	   
	   
	   // Using UrlValidator(String[] schemes, RegexValidator authorityValidator, long options) constructor
	   UrlValidator testVal2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("\nTesting isValid with allow all schemes on");	   
	   
	   System.out.println("http://www.google.com: " + testVal2.isValid("http://www.google.com"));
	   //System.out.println("https://www.google.com: " + testVal2.isValid("https://www.google.com"));
	   //System.out.println("ftp://www.google.com: " + testVal2.isValid("ftp://www.google.com"));
	   //System.out.println("test://www.google.com: " + testVal2.isValid("test://www.google.com"));
	   System.out.println("www.google.com: " + testVal2.isValid("www.google.com"));
	   System.out.println("http://255.255.255.255: " + testVal2.isValid("http://255.255.255.255"));
	   //System.out.println("https://255.255.255.255: " + testVal2.isValid("https://255.255.255.255"));
	   System.out.println("http://256.256.256.256: " + testVal2.isValid("http://256.256.256.256"));
	   //System.out.println("https://256.256.256.256: " + testVal2.isValid("https://256.256.256.256"));
	   System.out.println("http://www.google.com/hello?key=value: " + testVal2.isValid("http://www.google.com/hello?key=value"));
	   System.out.println("http://www.google.com:20/hello?key=value: " + testVal2.isValid("http://www.google.com:20/hello?key=value"));
	   System.out.println("http://www.google.com:20: " + testVal2.isValid("http://www.google.com:20"));	   
	   
	  

   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
    public void testIsValid()
   { 
	   //test isValid() with various UrlValidator objects
	   String[] schemes = {"http", "https", "ftp", "mailto", "irc", "file"};
	   testUrlValidators(schemes, null, UrlValidator.ALLOW_ALL_SCHEMES);
   }
   
   /***********************************************************************
    * Constructs 4 different UrlValidator objects uses them with isValid() 
    * and a test URL and compares the expected outcome to the actual 
    * outcome. The test URLs are built appending appending together URL
    * fragments. 
    * @param schemes
    * @param authorityValidator
    * @param options
    */
   public void testUrlValidators(String[] schemes, RegexValidator authorityValidator, long options) { 
	   UrlValidator urlValDef = new UrlValidator();
	   UrlValidator urlValSch = new UrlValidator(schemes);
	   UrlValidator urlValOpt = new UrlValidator(options);
	   UrlValidator urlValAll = new UrlValidator(schemes, authorityValidator, options);

	   //Test each object with null URLs
	   assertTrue(!urlValDef.isValid(null)); 
	   assertTrue(!urlValSch.isValid(null)); 
	   assertTrue(!urlValOpt.isValid(null)); 
	   assertTrue(!urlValAll.isValid(null));
	   
	   //Debugging single error tester
	   /*String url = "www.google.com:0/test1?action=view#foo"; 
	   assertEquals("Default - URL: " + url, 
			   false, 
			   urlValDef.isValid(url));*/
	   
	   int[] urlParts = {0, 0, 0, 0, 0, 0};
	   //test URL schemes
	   for (int sIndex = 0; sIndex < testUrlSchemeDefault.length; sIndex++) {
		   urlParts[0] = sIndex; 
		   //test authentication
		   for (int aIndex = 0; aIndex < testUrlAuthority.length; aIndex++) {
			   urlParts[1] = aIndex;
			   //test port
			   for (int pIndex = 0; pIndex < testUrlPort.length; pIndex++) {
				   urlParts[2] = pIndex;
				   for (int pathIndex = 0; pathIndex < testPath.length; pathIndex++) {
					   urlParts[3] = pathIndex;
					   for (int qIndex = 0; qIndex < testUrlQuery.length; qIndex++) {
						   urlParts[4] = qIndex;
						   for (int fIndex = 0; fIndex < testUrlFragment.length; fIndex++) {
							   urlParts[5] = fIndex; 
							   
							   /************* Unit test 1 ********************************
							   * Build URL, set expected result, and test isValid()
							   * for default constructor
							   **********************************************************/
							   StringBuilder urlBuffDef = new StringBuilder();
							   boolean expected = true;
							   for (int seg = 0; seg < testUrlParts.length; seg++) {
								   ResultPair[] pair = (ResultPair[])testUrlParts[seg];
								   urlBuffDef.append(pair[urlParts[seg]].item);
								   if (!pair[urlParts[seg]].valid) {
									   expected = false; 
								   }
							   }
							   //Run unit test with default constructor	
							   String testUrl = urlBuffDef.toString();
							   assertEquals("Default - URL: " + testUrl, 
									   expected, 
									   urlValDef.isValid(testUrl));
							   
							   /************* Unit test 2 ********************************
							   * Set expected result and test isValid() for custom scheme 
							   * constructor
							   **********************************************************/
							   expected = true; //Reset
							   ResultPair custScheme = (ResultPair)testUrlSchemeCustom[sIndex]; //
							   if (custScheme.valid) {
								   for (int seg = 1; seg < testUrlParts.length; seg++) {
									   ResultPair[] pair = (ResultPair[])testUrlParts[seg];
									   if (!pair[urlParts[seg]].valid) {
										   expected = false; 
									   }
								   }
							   } else {
								   expected = false;
							   }
							   //Run unit test for constructor with custom scheme					  
							   assertEquals("Schemes - URL: " + testUrl, 
									   expected, 
									   urlValSch.isValid(testUrl));
							   
							   /************* Unit test 3 ********************************
							   * Set expected result and test isValid() for all schemes 
							   * that match valid pattern
							   **********************************************************/
							   expected = true; //Reset
							   ResultPair allSchemes = (ResultPair)testUrlSchemeAll[sIndex]; //
							   if (allSchemes.valid) {
								   for (int seg = 1; seg < testUrlParts.length; seg++) {
									   ResultPair[] pair = (ResultPair[])testUrlParts[seg];
									   if (!pair[urlParts[seg]].valid) {
										   expected = false; 
									   }
								   }
							   } else {
								   expected = false;
							   } 
							   assertEquals("Options - URL: " + testUrl, 
									   expected, 
									   urlValOpt.isValid(testUrl));
							   assertEquals("All - URL: " + testUrl, 
									   expected, 
									   urlValAll.isValid(testUrl));
						   }
					   }
				   }
			   }
		   }
	   }
   }
   
   /*
    * The following ResultPair arrays originated from UrlValidatorTest.java
    * in the URLValidatorCorrect file. They have been modified here to provide 
    * more coverage of UrlValidator and its supporting files.
    */
   ResultPair[] testUrlSchemeDefault = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", false),
           new ResultPair("file://", false),
           new ResultPair("mailto://", false),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           //new ResultPair("", false) <------ pattern matcher mistakes authority as scheme
	};
   
   ResultPair[] testUrlSchemeCustom = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", false),
           new ResultPair("file://", true),
           new ResultPair("mailto://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)
	};
   
   ResultPair[] testUrlSchemeAll = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("file://", true),
           new ResultPair("mailto://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)
	};
	
	ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
	              new ResultPair("go.com", true),
	              new ResultPair("go.au", true),
	              new ResultPair("255.com", true),
	              new ResultPair("go.a", false),
	              new ResultPair("go.a1a", false),
	              new ResultPair("go.1aa", false),
	              new ResultPair("aaa.", false),
	              new ResultPair(".aaa", false),
	              new ResultPair("aaa", false),
	              new ResultPair("", false),
	              //IPv4 test cases
	              new ResultPair("-1.-1.-1.-1", false),
	      		  new ResultPair("0.0.0.0", true),
	      	      new ResultPair("255.255.255.255", true),
	      	      new ResultPair("256.256.256.256", false), 
	      	      new ResultPair("1.2.3.4.5", false),
	      	      new ResultPair("1.2.3.4.", false),
	      	      new ResultPair("1.2.3", false),
	      	      new ResultPair(".1.2.3.4", false)
	};
	        
	ResultPair[] testUrlPort = {new ResultPair(":-1", false),
	         new ResultPair(":0", true), 
	         new ResultPair(":1", true),
	         new ResultPair(":65534", true),
	         new ResultPair(":65535", true), //Maximum port number
	         new ResultPair(":65536",false),
	         new ResultPair(":FFFF", false),
	         new ResultPair("", true)
	};
	
	 ResultPair[] testPath = {new ResultPair("/test1", true),
             new ResultPair("/t123", true),
             new ResultPair("/$23", true),
             new ResultPair("/..", false),
             new ResultPair("/../", false),
             new ResultPair("/test1/", true),
             new ResultPair("", true),
             new ResultPair("/test1/file", true),
             new ResultPair("/..//file", false),
             new ResultPair("/test1//file", false)
	 };
	 
	 ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
             new ResultPair("?action=edit&mode=up", true),
             new ResultPair("", true)
	 };
	 
	 ResultPair[] testUrlFragment = {new ResultPair("#foo", true),
			 new ResultPair("#bar", true),
			 new ResultPair("#0", true),
			 new ResultPair("#30000000", true),
			 new ResultPair("", true)
	 };
	 
	 Object[] testUrlParts = {testUrlSchemeDefault, 
			 testUrlAuthority, 
			 testUrlPort, 
			 testPath, 
			 testUrlQuery, 
			 testUrlFragment
	};
}
