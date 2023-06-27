#include <iostream>
#include <string>
#include <memory>

// Video interface
class Video {
public:
    virtual void play() = 0;
    virtual ~Video() = default; 
};

// Concrete video classes
class PremiumVideo : public Video {
private:
    std::string title;

public:
    PremiumVideo(const std::string& title) : title(title) {}

    void play() override {
        std::cout << "Playing premium video: " << title << std::endl;
    }

    ~PremiumVideo() {
        std::cout << "PremiumVideo destructor called" << std::endl;
    }
};

class FreeVideo : public Video {
private:
    std::string title;

public:
    FreeVideo(const std::string& title) : title(title) {}

    void play() override {
        std::cout << "Playing free video: " << title << std::endl;
    }

    ~FreeVideo() {
        std::cout << "FreeVideo destructor called" << std::endl;
    }
};

// Video proxy class
class VideoProxy : public Video {
private:
    std::unique_ptr<Video> video;

public:
    VideoProxy(std::unique_ptr<Video> video) : video(std::move(video)) {}

    void play() override {
        std::cout << "Proxy: ";
        video->play();
    }

    ~VideoProxy() {
        std::cout << "VideoProxy destructor called" << std::endl;
    }
};

// Video factory class
class VideoFactory {
public:
    static std::unique_ptr<Video> createPremiumVideo(const std::string& title) {
        return std::make_unique<PremiumVideo>(title);
    }

    static std::unique_ptr<Video> createFreeVideo(const std::string& title) {
        return std::make_unique<FreeVideo>(title);
    }
};

// Client code
int main() {
    {
        std::unique_ptr<Video> premiumVideo = VideoFactory::createPremiumVideo("Premium Video 1");
        std::unique_ptr<Video> freeVideo = VideoFactory::createFreeVideo("Free Video 1");

        std::unique_ptr<Video> premiumVideoProxy = std::make_unique<VideoProxy>(std::move(premiumVideo));
        std::unique_ptr<Video> freeVideoProxy = std::make_unique<VideoProxy>(std::move(freeVideo));

        premiumVideoProxy->play();  // Proxy: Playing premium video: Premium Video 1
        freeVideoProxy->play();     // Proxy: Playing free video: Free Video 1
        
        std::cout << "bye" << std::endl;
    }
std::cout << "bdye" << std::endl;
    return 0;
}

