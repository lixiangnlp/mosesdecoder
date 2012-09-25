#ifndef moses_CrossingFeature_h
#define moses_CrossingFeature_h

#include "FeatureFunction.h"
#include "Word.h"

namespace Moses {
  
class InputType;
class ScoreIndexManager;
class ScoreComponentCollection;

class CrossingFeatureData
{
public:
  CrossingFeatureData(const std::vector<std::string> &toks);
  CrossingFeatureData(size_t length, const Word &lhs, bool isCrossing);
  
  bool operator<(const CrossingFeatureData &compare) const;
  
protected:
  int m_length;
  Word m_nonTerm;
  bool m_isCrossing;
};

class CrossingFeature : public StatefulFeatureFunction {
public:
  CrossingFeature(ScoreIndexManager &scoreIndexManager, const std::vector<float> &weights, const std::string &dataPath);
  virtual size_t GetNumScoreComponents() const;
  virtual std::string GetScoreProducerDescription(unsigned) const;
  virtual std::string GetScoreProducerWeightShortName(unsigned) const;
  virtual size_t GetNumInputScores() const;
  
  virtual const FFState* EmptyHypothesisState(const InputType &input) const;
  
  virtual FFState* Evaluate(
    const Hypothesis& currentHypothesis,
    const FFState* prev_state,
    ScoreComponentCollection* accumulator) const;
  
  virtual FFState* EvaluateChart(
    const ChartHypothesis& chartHypothesis,
    int featureId,
    ScoreComponentCollection* accumulator) const;
  

protected:
  std::string m_dataPath;
  std::map<CrossingFeatureData, float> m_data;

  bool LoadDataFile(const std::string &dataPath);
  float IsCrossing(const TargetPhrase& targetPhrase) const;

};

} // namespace Moses

#endif