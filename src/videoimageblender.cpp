#include "videoimageblender.h"

void VideoImageBlender::blend(YUV420 &videoFile, const YUV420Frame &imageFile, int numThreads)
{
    std::atomic<int> counter{0};

    std::vector<std::thread> threads;
    std::vector<YUV420Frame> &frames = videoFile.getFrames();

    for(size_t k = 0; k < numThreads; ++k)
    {
        int start = (frames.size() / numThreads) * k;
        int end = (k == numThreads - 1) ? frames.size() : (frames.size() / numThreads) * (k + 1);

        threads.emplace_back(std::thread([&frames, &imageFile, start, end, &counter](){
            
            for(size_t i = start; i < end; ++i)
            {
                OverlayProcessor::overlay(frames[i], imageFile, 0, 0);
                counter.fetch_add(1);
            }
        }));
        
    }

    for (auto& t : threads) 
    {
        t.join();
    }

    std:: cout << "\rFrames processed: " << counter  << " / " << frames.size() << std::endl;
}

