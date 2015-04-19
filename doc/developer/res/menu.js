function headerAndContentsMenu(pageName, relativePath) {
    doHeaderAndContentsMenu(pageName, relativePath, 49, 133, 155,
                            { "menuItems": [
                                { "level": 0, "label": "Home", "link": "developer/index.html" },
                                { "separator": true },
                                { "level": 0, "label": "Prerequisites", "link": "developer/prerequisites.html" },
                                { "separator": true },
                                { "level": 0, "label": "File structure", "link": "developer/fileStructure.html" },
                                { "separator": true },
                                { "level": 0, "label": "Develop", "link": "developer/develop/index.html" },
                                { "level": 1, "label": "Coding style", "link": "developer/develop/codingStyle.html" },
                                { "level": 1, "label": "Plugins", "link": "developer/develop/plugins/index.html", "subMenu": [
                                    { "level": 2, "label": "Sample", "link": "developer/develop/plugins/Sample.html" },
                                    { "level": 2, "label": "SampleTools", "link": "developer/develop/plugins/SampleTools.html" },
                                    { "level": 2, "label": "SampleWindow", "link": "developer/develop/plugins/SampleWindow.html" },
                                    { "level": 2, "label": "SampleView", "link": "developer/develop/plugins/SampleView.html" },
                                  ]
                                },
                                { "level": 1, "label": "Internationalisation", "link": "developer/develop/internationalisation.html" },
                                { "level": 1, "label": "Tests", "link": "developer/develop/tests.html" },
                                { "level": 0, "label": "Build, test and run", "link": "developer/buildTestAndRun.html" },
                                { "level": 0, "label": "Functional tests", "link": "developer/functionalTests.html" },
                                { "level": 0, "label": "Package", "link": "developer/package.html" },
                                { "separator": true },
                                { "level": 0, "label": "Third-party libraries", "link": "developer/thirdPartyLibraries.html" },
                                { "separator": true },
                                { "level": 0, "label": "Git repository", "link": "https://github.com/opencor/opencor", "directLink": true },
                                { "level": 0, "label": "Latest commits", "link": "https://github.com/opencor/opencor/commits", "directLink": true },
                                { "level": 0, "label": "Current bugs, feature requests, etc.", "link": "https://github.com/opencor/opencor/issues", "directLink": true },
                                { "separator": true },
                                { "level": 0, "label": "Published article", "link": "http://dx.doi.org/10.3389/fphys.2015.00026", "directLink": true },
                                { "separator": true },
                                { "level": 0, "label": "Contact us", "link": "user/contactUs.html" },
                              ]
                            });
}
